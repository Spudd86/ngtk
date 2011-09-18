OBJS = \
	ngtk-component.o \
	ngtk-container.o \
	ngtk-event-generator.o \
	ngtk-layout.o

all: ngtk-widgets.a

ngtk-widgets.a: $(OBJS)
	$(AR) $(ARFLAGS) ngtk-widgets.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
