# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
* Xlib header files


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

```shell
make install
```


## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

```shell
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```shell
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)


## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
