all: libngtk-utils.a

libngtk-utils.a: ngtk-list.o
	$(NGTK_MKS) libngtk-utils.a  ngtk-list.o

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
