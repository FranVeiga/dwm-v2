# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.

This is my second configuration of dwm.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Assuming you have a display manager installed, move the file named
dwm.desktop to /usr/share/xsessions, and you then should be able to
select it from your display manager.

## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
