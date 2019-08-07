
Debian
====================
This directory contains files used to package tmicoind/tmicoin-qt
for Debian-based Linux systems. If you compile tmicoind/tmicoin-qt yourself, there are some useful files here.

## tmicoin: URI support ##


tmicoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tmicoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your tmicoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/tmicoin128.png` to `/usr/share/pixmaps`

tmicoin-qt.protocol (KDE)

