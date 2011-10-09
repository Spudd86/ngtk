include MakeConfig.mk

export NGTK_MKS=$(AR) $(ARFLAGS)
export NGTK_MKD=$(LD) $(LDFLAGS)
export NGTK_MKO=$(CC) $(CFLAGS) -g -Wall -Werror $(NGTK_CFLAGS) -c

all: ngtk-core ngtk-backend-subdirs

ngtk-core: dist/libngtk$(DLEXT)

dist/libngtk$(DLEXT): ngtk-subdirs
	mkdir -p dist
	$(NGTK_MKD) object-system/*.a utils/*.a widgets/*.a -o dist/libngtk$(DLEXT)

ngtk-subdirs:
	cd object-system; $(MAKE) $(MFLAGS)
	cd utils;         $(MAKE) $(MFLAGS)
	cd widgets;       $(MAKE) $(MFLAGS)

clean: .PHONY
	cd object-system; $(MAKE) $(MFLAGS) clean
	cd utils;         $(MAKE) $(MFLAGS) clean
	cd widgets;       $(MAKE) $(MFLAGS) clean

ifeq ($(NGTK_BUILD_NCURSES), TRUE)
	cd backends;      $(MAKE) $(MFLAGS) clean-backend-nc
endif

ifeq ($(NGTK_BUILD_XLIB), TRUE)
	cd backends;      $(MAKE) $(MFLAGS) clean-backend-xlib
endif

ifeq ($(NGTK_BUILD_WINAPI), TRUE)
	cd backends;      $(MAKE) $(MFLAGS) clean-backend-windows
endif
	-rm -rf dist/

ngtk-backend-subdirs: .PHONY

ifeq ($(NGTK_BUILD_NCURSES), TRUE)
	$(info Building NCURSES backend)
	cd backends;      $(MAKE) $(MFLAGS) backend-nc
endif

ifeq ($(NGTK_BUILD_XLIB), TRUE)
	$(info Building X11-Xlib backend)
	cd backends;      $(MAKE) $(MFLAGS) backend-xlib
endif

ifeq ($(NGTK_BUILD_WINAPI), TRUE)
	$(info Building WinApi-Windows backend)
	cd backends;      $(MAKE) $(MFLAGS) backend-windows
endif

.PHONY:
	true
