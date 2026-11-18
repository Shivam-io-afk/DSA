#!/usr/bin/env python3
"""clip-watcher: record a live Twitch/YouTube stream and auto-clip chat spikes.

Pipeline: streamlink -> rec/*.ts, anonymous IRC chat -> 10 s buckets ->
spike detection -> ffmpeg 9:16 clip -> whisper .srt
"""
import argparse
import json
import queue
import re
import shutil
import socket
import statistics
import subprocess
import sys
import threading
import time
import urllib.request
from collections import deque
from pathlib import Path

IRC_HOST, IRC_PORT, IRC_NICK = "irc.chat.twitch.tv", 6667, "justinfan12345"
BUCKET = 10          # seconds per bucket
WINDOW = 180         # seconds of history the median is taken over
WARMUP = 6           # buckets of history required before spikes can fire
FLUSH_MARGIN = 8     # extra seconds to let the recording catch up before cutting


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


class SpikeDetector:
    """A bucket is a spike if it has >= factor x the median of the previous
    WINDOW seconds of buckets, and at least `min_msgs` messages."""

    def __init__(self, factor=2.5, min_msgs=10):
        self.factor, self.min_msgs = factor, min_msgs
        self.history = deque(maxlen=WINDOW // BUCKET)

    def add(self, count):
        median = statistics.median(self.history) if self.history else 0
        spike = (len(self.history) >= WARMUP
                 and count >= self.min_msgs
                 and count >= self.factor * median)
        self.history.append(count)
        return spike, median


def twitch_chat(channel, stop):
    """Yield True once per chat message, and None about once a second (a tick),
    reconnecting forever until `stop` is set."""
    while not stop.is_set():
        try:
            with socket.create_connection((IRC_HOST, IRC_PORT), timeout=15) as s:
                s.sendall(f"NICK {IRC_NICK}\r\nJOIN #{channel}\r\n".encode())
                s.settimeout(1)
                log(f"chat: joined #{channel}")
                buf = b""
                while not stop.is_set():
                    try:
                        data = s.recv(4096)
                    except socket.timeout:
                        yield None
                        continue
                    if not data:
                        raise ConnectionError("server closed the connection")
                    buf += data
                    *lines, buf = buf.split(b"\r\n")
                    for line in lines:
                        if line.startswith(b"PING"):
                            s.sendall(b"PONG" + line[4:] + b"\r\n")
                        elif b" PRIVMSG #" in line:
                            yield True
                    yield None
        except OSError as e:
            log(f"chat: {e}; reconnecting in 5 s")
            stop.wait(5)


YT_UA = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
                       "(KHTML, like Gecko) Chrome/126.0 Safari/537.36",
         "Accept-Language": "en-US,en;q=0.9", "Cookie": "SOCS=CAI"}


def yt_get(url, body=None):
    data = json.dumps(body).encode() if body is not None else None
    headers = dict(YT_UA, **({"Content-Type": "application/json"} if data else {}))
    with urllib.request.urlopen(urllib.request.Request(url, data, headers), timeout=15) as r:
        return r.read().decode("utf-8", "replace")


def youtube_video_id(target):
    """Video id from a watch/live/youtu.be URL, or the current live video of a
    channel URL such as youtube.com/@handle."""
    m = re.search(r"(?:[?&]v=|youtu\.be/|/live/|/shorts/|/embed/)([\w-]{11})", target)
    if m:
        return m.group(1)
    url = target if "://" in target else "https://" + target
    page = yt_get(url.split("?")[0].rstrip("/").removesuffix("/live") + "/live")
    m = (re.search(r'<link rel="canonical" href="[^"]*[?&]v=([\w-]{11})', page)
         or re.search(r'"videoId":"([\w-]{11})"', page))
    if not m:
        sys.exit(f"could not find a live video at {target} - is the channel live?")
    return m.group(1)


def _find(obj, key):
    """All values stored under `key` anywhere inside nested JSON, in order."""
    if isinstance(obj, dict):
        for k, v in obj.items():
            if k == key:
                yield v
            yield from _find(v, key)
    elif isinstance(obj, list):
        for v in obj:
            yield from _find(v, key)


def youtube_chat(video_id, stop):
    """Same contract as twitch_chat, polling YouTube's web live-chat endpoint
    (no API key or login)."""
    while not stop.is_set():
        try:
            page = yt_get(f"https://www.youtube.com/live_chat?is_popout=1&v={video_id}")
            key = re.search(r'"INNERTUBE_API_KEY":"([^"]+)"', page).group(1)
            version = re.search(r'"clientVersion":"([^"]+)"', page).group(1)
            raw = re.search(r'ytInitialData"?\]?\s*=\s*(\{.*?\});\s*</script>', page, re.S).group(1)
            chat = next(_find(json.loads(raw), "liveChatRenderer"))
            # prefer "Live chat" (every message) over the default "Top chat"
            reloads = [c["continuation"] for c in _find(chat.get("header", {}), "reloadContinuationData")]
            cont = reloads[-1] if reloads else next(_find(chat["continuations"], "continuation"))
            log(f"chat: joined YouTube live chat {video_id}")
            first = True
            while not stop.is_set():
                resp = json.loads(yt_get(
                    f"https://www.youtube.com/youtubei/v1/live_chat/get_live_chat?key={key}&prettyPrint=false",
                    {"context": {"client": {"clientName": "WEB", "clientVersion": version}},
                     "continuation": cont}))
                live = resp.get("continuationContents", {}).get("liveChatContinuation")
                if live is None:
                    raise ConnectionError("live chat is not available (stream ended or chat disabled)")
                if not first:       # the first reply is backlog, not new messages
                    for item in _find(live.get("actions", []), "addChatItemAction"):
                        if any(k in item.get("item", {}) for k in
                               ("liveChatTextMessageRenderer", "liveChatPaidMessageRenderer")):
                            yield True
                first = False
                cont = next(_find(live["continuations"], "continuation"))
                wait = min(max(next(_find(live["continuations"], "timeoutMs"), 1000) / 1000, 0.5), 5)
                yield None
                stop.wait(wait)
        except (OSError, AttributeError, KeyError, StopIteration, ValueError) as e:
            log(f"chat: {type(e).__name__}: {e}; retrying in 5 s")
            yield None
            stop.wait(5)


def cut_clip(rec, start, duration, out):
    """Cut [start, start+duration] out of the recording, center-cropped to 9:16."""
    cmd = ["ffmpeg", "-hide_banner", "-loglevel", "error", "-y",
           "-ss", f"{start:.2f}", "-i", str(rec), "-t", f"{duration:.2f}",
           "-vf", "crop=trunc(ih*9/16/2)*2:ih",
           "-c:v", "libx264", "-preset", "veryfast", "-crf", "20",
           "-c:a", "aac", "-movflags", "+faststart", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    ok = r.returncode == 0 and out.exists() and out.stat().st_size > 0
    if not ok:
        log(f"ffmpeg failed for {out.name}: {r.stderr.strip()[-300:]}")
    return ok


def transcribe(clip, model):
    r = subprocess.run(["whisper", str(clip), "--model", model,
                        "--output_format", "srt", "--output_dir", str(clip.parent),
                        "--verbose", "False"], capture_output=True, text=True)
    srt = clip.with_suffix(".srt")
    if r.returncode == 0 and srt.exists():
        log(f"srt:  {srt}")
    else:
        log(f"whisper failed for {clip.name}: {r.stderr.strip()[-300:]}")


def clip_worker(jobs, rec, rec_start, args, stop):
    """Runs clips one at a time so ffmpeg/whisper never block chat reading."""
    while True:
        spike_t = jobs.get()
        if spike_t is None:
            return
        # Wait for the "after" part to be recorded (skipped when shutting down).
        while not stop.is_set() and time.time() < spike_t + args.after + FLUSH_MARGIN:
            time.sleep(0.5)
        pos = spike_t - rec_start + args.offset     # spike position in the file
        start = max(0.0, pos - args.before)
        duration = pos + args.after - start
        if duration <= 1:
            continue
        out = Path("clips") / f"{args.channel}_{time.strftime('%Y%m%d_%H%M%S', time.localtime(spike_t))}.mp4"
        if cut_clip(rec, start, duration, out):
            log(f"clip: {out}")
            if not args.no_srt:
                transcribe(out, args.model)


def main():
    p = argparse.ArgumentParser(description="Record a Twitch or YouTube live stream and clip chat spikes.")
    p.add_argument("channel", help="Twitch channel name, or a YouTube live/channel URL")
    p.add_argument("--min", type=int, default=10, dest="min_msgs",
                   help="minimum messages in a 10 s bucket to count as a spike (default 10; quiet chats: 5)")
    p.add_argument("--factor", type=float, default=2.5, help="spike = factor x median (default 2.5)")
    p.add_argument("--before", type=float, default=20, help="seconds before the spike (default 20)")
    p.add_argument("--after", type=float, default=10, help="seconds after the spike (default 10)")
    p.add_argument("--offset", type=float, default=0,
                   help="shift every clip by this many seconds if they land early/late")
    p.add_argument("--quality", default="best", help="streamlink quality (default best)")
    p.add_argument("--model", default="base", help="whisper model (default base)")
    p.add_argument("--no-srt", action="store_true", help="skip whisper subtitles")
    args = p.parse_args()
    youtube = bool(re.search(r"youtube\.com|youtu\.be", args.channel))

    needed = ["ffmpeg", "streamlink"] + ([] if args.no_srt else ["whisper"])
    missing = [t for t in needed if not shutil.which(t)]
    if missing:
        sys.exit(f"missing: {', '.join(missing)}  ->  install ffmpeg, then: pip install streamlink openai-whisper")

    Path("rec").mkdir(exist_ok=True)
    Path("clips").mkdir(exist_ok=True)
    if youtube:
        args.channel = youtube_video_id(args.channel)       # also names the files
        url, chat = f"https://www.youtube.com/watch?v={args.channel}", youtube_chat
        sl_cmd = ["streamlink"]
    else:
        args.channel = args.channel.lower().lstrip("#").rsplit("/", 1)[-1]
        url, chat = f"https://twitch.tv/{args.channel}", twitch_chat
        sl_cmd = ["streamlink", "--twitch-disable-ads"]
    rec = Path("rec") / f"{args.channel}_{time.strftime('%Y%m%d_%H%M%S')}.ts"

    # 1) record the stream (.ts stays readable while it is still being written)
    sl = subprocess.Popen(sl_cmd + ["-o", str(rec), url, args.quality],
                          stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True)
    log(f"waiting for {args.channel}'s stream...")
    while not (rec.exists() and rec.stat().st_size > 0):
        if sl.poll() is not None:
            sys.exit(f"streamlink exited - is {args.channel} live?\n{sl.stderr.read().strip()[-500:]}")
        time.sleep(0.2)
    rec_start = time.time()
    log(f"rec:  {rec}")

    stop = threading.Event()
    jobs = queue.Queue()
    worker = threading.Thread(target=clip_worker, args=(jobs, rec, rec_start, args, stop))
    worker.start()

    # 2-3) read chat, count 10 s buckets, detect spikes
    det = SpikeDetector(args.factor, args.min_msgs)
    count, bucket_start, last_spike = 0, time.time(), 0.0
    try:
        for msg in chat(args.channel, stop):
            if msg:
                count += 1
            now = time.time()
            if now - bucket_start >= BUCKET:
                spike, median = det.add(count)
                # skip spikes that would overlap the previous clip
                if spike and bucket_start - last_spike >= args.before + args.after:
                    log(f"SPIKE: {count} msgs/10s (median {median:g}) -> clipping")
                    jobs.put(bucket_start)      # 4-5) cut + subtitle in the worker
                    last_spike = bucket_start
                else:
                    log(f"chat: {count} msgs/10s (median {median:g})")
                count, bucket_start = 0, now
            if sl.poll() is not None:
                log("stream ended")
                break
    except KeyboardInterrupt:
        log("stopping...")
    finally:
        stop.set()
        if sl.poll() is None:
            sl.terminate()
            sl.wait()
        jobs.put(None)
        worker.join()       # finish any pending clips
        log("done")


if __name__ == "__main__":
    main()
