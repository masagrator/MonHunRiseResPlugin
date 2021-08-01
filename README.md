# MonHunRiseResPlugin
Skyline plugin for Monster Hunter Rise to override resolution

# End-user Usage
In release there are files that by default are setting handheld resolution to 720p and docked to 1080p.
If you want to change anything, you need to use "MHRiseResolution.py". It is required to have Python 3 and "keystone-engine" python library installed.

It wasn't tested on Japanese release. Only Western.

Put folder `0100B04011742000` to `atmosphere\contents` and start game.
Boot time may be increased by few seconds.
It should work with all game versions (confirmed working on 2.0.0 and 3.2.0).

# Notes
- subsdk9 file in release is uncompressed so it's easily editable with python script. Compiling manually plugin will result in compressed plugin. To uncompress it use hactool.

# Thanks to
- The Skyline Project
- cucholix for testing