#!/usr/bin/env bash
# Usage: ./watch.sh <twitch_channel | youtube_url> [--min N] [--no-srt] ...   (see --help)
set -euo pipefail
cd "$(dirname "$0")"
if [ $# -lt 1 ]; then
  echo "usage: ./watch.sh <twitch_channel | youtube_url> [--min N]" >&2
  exit 1
fi
exec python3 watch.py "$@"
