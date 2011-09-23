OBJS = \
	ngtk-xlib-base.o \
	ngtk-xlib-component.o \
	ngtk-xlib-container.o \
	ngtk-xlib-defs.o \
	ngtk-xlib-event-generator.o \
	ngtk-xlib-window.o

all: libngtk-backend-xlib.a

libngtk-backend-xlib.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-xlib.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
