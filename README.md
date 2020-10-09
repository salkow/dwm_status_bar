A status bar for dwm.

TODO:
- [ ] List all features in README.
- [ ] Move all code in src folder.
- [ ] Add option for the location of the fifo file.
- [ ] Fix bug where programs exits when wttr.in isn't available in the weather module.
- [x] Add volume event.
- [ ] Create program for signaling.
- [ ] Add internet module.
- [ ] Cleanup Makefile.
- [ ] Add option to specify location in weather module. 
- [ ] List dependencies in README.
- [x] Add mpd module.
- [x] Add mpd event.
- [x] Make each module in the statusbar, clickable.
- [ ] Make a patch for dwm to notify statusbar when something has been clicked.
- [ ] Maybe make the modules patches.
- [ ] Prevent user from opening multiple instances of dwm_status_bar.
- [ ] Add more error checking.
 
For the keyboard_language module I used code from https://github.com/grwlf/xkb-switch.
I modified it, removing some stuff, to only use what was needed.

For the volume module I used code from:
https://git.alsa-project.org/?p=alsa-utils.git;a=blob;f=alsactl/monitor.c;hb=HEAD

For the mpd module I used code from:
https://github.com/MusicPlayerDaemon/mpc
