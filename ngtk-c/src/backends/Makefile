single_target_name=ngtk_backend.a

backend-basic: .PHONY
	cd basic; $(MAKE) $(MFLAGS)

clean-backend-basic: .PHONY
	cd basic; $(MAKE) clean


backend-nc: .PHONY backend-basic
	cd nc; $(MAKE) $(MFLAGS)
	$(AR) $(ARFLAGS) $(single_target_name) basic/ngtk-backend-basic.a nc/ngtk-backend-nc.a

clean-backend-nc: .PHONY clean-backend-basic
	cd nc; $(MAKE) clean
	rm $(single_target_name)


.PHONY:
	true
