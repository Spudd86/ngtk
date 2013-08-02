all: libngtk-utils.a

libngtk-utils.a: ngtk-list.o ngtk-memory.o
	$(NGTK_MKS) libngtk-utils.a  ngtk-list.o ngtk-memory.o

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a
