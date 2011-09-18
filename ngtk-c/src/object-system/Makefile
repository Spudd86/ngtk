all: ngtk-object-system.a

ngtk-object-system.a: ngtk-object.o
	$(AR) $(ARFLAGS) ngtk-object-system.a ngtk-object.o

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
