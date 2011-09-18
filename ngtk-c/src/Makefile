export NGTK_MKS=$(AR) rcs
export NGTK_MKD=ld --whole-archive -shared -fPIC -o

all:   dist/libngtk.so

clean: .SUBDIRS-CLEAN
	rm -rf dist

.SUBDIRS: .PHONY
	cd object-system; $(MAKE) $(MFLAGS)
	cd utils;         $(MAKE) $(MFLAGS)
	cd widgets;       $(MAKE) $(MFLAGS)
	cd backends;      $(MAKE) backend-nc

.SUBDIRS-CLEAN: .PHONY
	cd object-system; $(MAKE) clean
	cd utils;         $(MAKE) clean
	cd widgets;       $(MAKE) clean
	cd backends;      $(MAKE) clean-backend-nc

dist/libngtk.so: .SUBDIRS
	mkdir -p dist
	$(NGTK_MKD) dist/libngtk.so object-system/*.a utils/*.a widgets/*.a

.PHONY:
	true
