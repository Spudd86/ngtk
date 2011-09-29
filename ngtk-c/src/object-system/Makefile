all: libngtk-object-system.a

libngtk-object-system.a: ngtk-object.o
	$(NGTK_MKS) libngtk-object-system.a ngtk-object.o

%.o: %.c
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
