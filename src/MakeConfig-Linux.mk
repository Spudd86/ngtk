export DLEXT       = .so
export EXEEXT      =

export CC          = gcc
export CFLAGS      = -fPIC

export AR          = ar
export ARFLAGS     = rc

export RANLIB      = ranlib
export RANLIBFLAGS =

export LD          = ld
export LDFLAGS     = --whole-archive -shared

export CCLDEFLAGS  =

export NGTK_BUILD_XLIB    = TRUE
export NGTK_BUILD_NCURSES = TRUE
export NGTK_BUILD_WINAPI  = FALSE