all:   dist/ngtk.a

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

dist/ngtk.a: .SUBDIRS
	mkdir -p dist
	$(AR) $(ARFLAGS) dist/ngtk.a backends/*.a object-system/*.a utils/*.a widgets/*.a

.PHONY:
	true
