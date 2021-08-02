# MonHunRiseResPlugin
Skyline plugin for Monster Hunter Rise to override resolution

# End-user Usage
In release there are files that by default are setting handheld resolution to 720p and docked to 1080p.

If you want to change anything, you need to use "Patch.cmd". 
It is required to have `Windows`, `Python 3` and "keystone-engine" python library installed for it to work.

```cmd
pip3 install keystone-engine
```

For other systems you need to manually compile nsnsotool</br>
https://github.com/0CBH0/nsnsotool</br>
And use it for decompression and compression of subsdk9

It wasn't tested on Japanese release. Only Western.

Put folder `0100B04011742000` to `atmosphere\contents` and start game.</br>
Boot time may be increased by few seconds.</br>
It should work with all game versions (confirmed working on 2.0.0 and 3.2.0).

# Thanks to
- The Skyline Project
- cucholix for testing
