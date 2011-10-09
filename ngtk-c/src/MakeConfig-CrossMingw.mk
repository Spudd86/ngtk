export DLEXT       = .dll
export EXEEXT      = .exe

export CC          = i686-pc-mingw32-gcc
export CFLAGS      =

export AR          = i686-pc-mingw32-ar
export ARFLAGS     = rc

export RANLIB      = i686-pc-mingw32-ranlib
export RANLIBFLAGS =

export LD          = i686-pc-mingw32-ld
export LDFLAGS     = --whole-archive -shared -lmsvcrt -L/usr/i686-pc-mingw32/sys-root/mingw/lib

export NGTK_BUILD_XLIB    = FALSE
export NGTK_BUILD_NCURSES = FALSE
export NGTK_BUILD_WINAPI  = TRUE