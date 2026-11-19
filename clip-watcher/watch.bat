@echo off
rem Usage: watch.bat CHANNEL_OR_YOUTUBE_URL [--min N] ...   (see --help)
pushd "%~dp0"
python watch.py %*
popd
