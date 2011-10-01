all: libngtk-utils.a

libngtk-utils.a: ngtk-list.o ngtk-memory.o
	$(NGTK_MKS) libngtk-utils.a  ngtk-list.o ngtk-memory.o

%.o: %.c %.h
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
