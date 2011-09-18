all: ngtk-utils.a

ngtk-utils.a: ngtk-list.o
	$(AR) $(ARFLAGS) ngtk-utils.a  ngtk-list.o

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
