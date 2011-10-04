OBJS = \
	ngtk-nc-backend.o \
	ngtk-nc-component.o \
	ngtk-nc-container.o \
	ngtk-nc-defs.o \
	ngtk-nc-graphics.o \
	ngtk-nc-window.o

all: libngtk-backend-nc.a

libngtk-backend-nc.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-nc.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
