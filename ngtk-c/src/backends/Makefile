dist_dir=dist

backend-basic: .PHONY
	cd basic; $(MAKE) $(MFLAGS)

clean-backend-basic: .PHONY
	cd basic; $(MAKE) clean

backend-nc: .PHONY backend-basic dist_dir
	cd nc; $(MAKE) $(MFLAGS)
	$(NGTK_MKD) $(dist_dir)/libngtk-backend-nc.so basic/libngtk-backend-basic.a nc/libngtk-backend-nc.a

clean-backend-nc: .PHONY clean-backend-basic
	cd nc; $(MAKE) clean
	rm -rf $(dist_dir)

dist_dir:
	mkdir -p $(dist_dir)

.PHONY:
	true
