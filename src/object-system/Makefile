all: libngtk-object-system.a

libngtk-object-system.a: ngtk-object.o
	$(NGTK_MKS) libngtk-object-system.a ngtk-object.o

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a
