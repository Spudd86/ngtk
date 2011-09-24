OBJS = \
	ngtk-nc-base.o \
	ngtk-nc-component.o \
	ngtk-nc-container.o \
	ngtk-nc-defs.o \
	ngtk-nc-event-generator.o \
	ngtk-nc-window.o

all: libngtk-backend-nc.a

libngtk-backend-nc.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-nc.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
