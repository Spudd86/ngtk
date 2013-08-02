export DLEXT       = .dll
export EXEEXT      = .exe

export CC          = gcc
export CFLAGS      =

export AR          = ar
export ARFLAGS     = rc

export RANLIB      = ranlib
export RANLIBFLAGS =

export LD          = ld
export LDFLAGS     = --whole-archive -shared --enable-auto-import -lmsvcrt -lkernel32 -lUser32

export CCLDEFLAGS  =

export NGTK_BUILD_XLIB    = FALSE
export NGTK_BUILD_NCURSES = FALSE
export NGTK_BUILD_WINAPI  = TRUE