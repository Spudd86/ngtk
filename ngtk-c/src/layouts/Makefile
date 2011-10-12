all: libngtk-layouts.a

libngtk-layouts.a: ngtk-grid-layout.o
	$(NGTK_MKS) libngtk-layouts.a ngtk-grid-layout.o

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a
