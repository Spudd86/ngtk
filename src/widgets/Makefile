OBJS = \
	ngtk-base.o \
	ngtk-backend.o \
	ngtk-component.o \
	ngtk-container.o \
	ngtk-layout.o

all: libngtk-widgets.a

libngtk-widgets.a: $(OBJS)
	$(NGTK_MKS) libngtk-widgets.a $(OBJS)

%.o: %.c %.h ngtk-widget-types.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a