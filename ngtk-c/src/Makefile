export NGTK_MKS=$(AR) rcs
export NGTK_MKD=ld --whole-archive -shared -fPIC -o
CC+=-g -Wall -Werror $(NGTK_CFLAGS)
export CC
all:   dist/libngtk.so

clean: .SUBDIRS-CLEAN
	rm -rf dist

.SUBDIRS: .PHONY
	cd object-system; $(MAKE) $(MFLAGS)
	cd utils;         $(MAKE) $(MFLAGS)
	cd widgets;       $(MAKE) $(MFLAGS)
#	cd backends;      $(MAKE) $(MFLAGS) backend-nc
	cd backends;      $(MAKE) $(MFLAGS) backend-xlib

.SUBDIRS-CLEAN: .PHONY
	cd object-system; $(MAKE) $(MFLAGS) clean
	cd utils;         $(MAKE) $(MFLAGS) clean
	cd widgets;       $(MAKE) $(MFLAGS) clean
	cd backends;      $(MAKE) $(MFLAGS) clean-backend-nc
	cd backends;      $(MAKE) $(MFLAGS) clean-backend-xlib

dist/libngtk.so: .SUBDIRS
	mkdir -p dist
	$(NGTK_MKD) dist/libngtk.so object-system/*.a utils/*.a widgets/*.a

.PHONY:
	true
