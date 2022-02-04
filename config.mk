# dwm version
VERSION = 6.2-rx

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2

# includes and libs
INCS = -I$(X11INC) -I$(FREETYPEINC)
LIBS = -L$(X11LIB) $(FREETYPELIBS) -lX11

# flags
CFLAGS = $(INCS) -std=c99 -Wall -Wextra -Wpedantic -Wno-parentheses -O2 -march=native -pipe -D_DEFAULT_SOURCE -DVERSION=\"$(VERSION)\"
LDFLAGS = $(LIBS)
