@echo off
rem Usage: watch.bat <twitch_channel | youtube_url> [--min N] ...   (see --help)
pushd "%~dp0"
python watch.py %*
popd
