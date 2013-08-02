OBJS = \
	ngtk-xlib-backend.o \
	ngtk-xlib-component.o \
	ngtk-xlib-container.o \
	ngtk-xlib-defs.o \
	ngtk-xlib-graphics.o \
	ngtk-xlib-window.o

all: libngtk-backend-xlib.a

libngtk-backend-xlib.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-xlib.a $(OBJS)

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a
