OBJS = \
	ngtk-component.o \
	ngtk-container.o \
	ngtk-event-generator.o \
	ngtk-layout.o

all: libngtk-widgets.a

libngtk-widgets.a: $(OBJS)
	$(NGTK_MKS) libngtk-widgets.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
