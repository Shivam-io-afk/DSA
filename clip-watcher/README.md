# clip-watcher

Records a live Twitch or YouTube stream and automatically cuts vertical clips whenever chat spikes.

```
./watch.sh <twitch_channel>
./watch.sh "https://www.youtube.com/watch?v=VIDEO_ID"    # or https://www.youtube.com/@handle
```

On Windows (PowerShell or cmd) use `.\watch.bat` instead of `./watch.sh`, with the same arguments.

**Finished YouTube streams** work too: give the video URL of a past live stream and it
downloads the saved chat replay, finds the spikes, and downloads only those parts of the
video (needs `pip install yt-dlp`).

1. `streamlink` records the live stream to `rec/`.
2. Chat is read anonymously: Twitch over IRC, YouTube via the web live-chat endpoint
   (no token or API key needed).
3. Messages are counted in 10 s buckets; a spike is a bucket with at least 2.5x the
   median of the last 3 minutes **and** at least `--min` messages.
4. For each spike, `ffmpeg` cuts 20 s before + 10 s after into `clips/`, center-cropped to 9:16.
5. Whisper writes an `.srt` next to each clip.

## Install

```
# ffmpeg from your package manager, then:
pip install streamlink openai-whisper yt-dlp
```

## Options

| Flag | Default | Meaning |
|---|---|---|
| `--min N` | 10 | minimum messages per 10 s bucket (quiet chats: `--min 5`) |
| `--factor X` | 2.5 | spike threshold as a multiple of the median |
| `--before S` / `--after S` | 20 / 10 | seconds kept around the spike |
| `--offset S` | 0 | shift all clips if they land early (+) or late (-) |
| `--quality Q` | best | streamlink quality, e.g. `720p60` |
| `--model M` | base | whisper model (`tiny`, `small`, ...) |
| `--no-srt` | | skip subtitles |
| `--max-height N` | 1080 | YouTube replay: highest video resolution to download |
| `--cookies-from-browser B` | | YouTube replay: use your browser's YouTube login (`chrome`, `firefox`, ...) if YouTube says "confirm you're not a bot" |

Stop with Ctrl-C; clips already queued are finished first.

## Notes

- YouTube streams usually run further behind real time than Twitch; if clips start too
  late or early, tune `--offset`.
- Twitch only works while the channel is live; YouTube also works on finished streams
  that kept their chat replay.
- Spikes need about a minute of chat history before they can fire.
- Spikes closer together than one clip length are merged into the first clip.
- Only clip streamers who allow it.
