# xcompmgr fixs
## Weird steam transparant games
There is a bug that when running xcompgr steam games on boot appear to run and have their window, but is hidden/invisable.

Relates to:
- [[Solved] Steam windows still drawing when hidden](https://bbs.archlinux.org/viewtopic.php?pid=1384701#p1384701)

### Potential Fixs
1. `/etc/X11/xorg.conf.d/70-nvidia-composite-hotfix.conf`
```
Section "Extensions"
    Option         "Composite" "Enable"
EndSection
```
