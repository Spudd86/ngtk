dist_dir=dist

backend-basic: .PHONY
	cd basic; $(MAKE) $(MFLAGS)

clean-backend-basic: .PHONY
	cd basic; $(MAKE) clean

backend-nc: .PHONY backend-basic dist_dir
	cd nc; $(MAKE) $(MFLAGS)
	$(NGTK_MKD) -o $(dist_dir)/libngtk-backend-nc$(DLEXT) basic/libngtk-backend-basic.a nc/libngtk-backend-nc.a

backend-xlib: .PHONY backend-basic dist_dir
	cd xlib; $(MAKE) $(MFLAGS)
	$(NGTK_MKD) -o $(dist_dir)/libngtk-backend-xlib$(DLEXT) basic/libngtk-backend-basic.a xlib/libngtk-backend-xlib.a

backend-windows: .PHONY backend-basic dist_dir
	cd windows; $(MAKE) $(MFLAGS)
	$(NGTK_MKD) -o $(dist_dir)/libngtk-backend-windows$(DLEXT) basic/libngtk-backend-basic.a windows/libngtk-backend-windows.a

clean-backend-nc: .PHONY clean-backend-basic
	cd nc; $(MAKE) clean
	rm -rf $(dist_dir)

clean-backend-xlib: .PHONY clean-backend-basic
	cd xlib; $(MAKE) clean
	rm -rf $(dist_dir)

clean-backend-windows: .PHONY clean-backend-basic
	cd windows; $(MAKE) clean
	rm -rf $(dist_dir)

dist_dir:
	mkdir -p $(dist_dir)
	
.PHONY:
	@true