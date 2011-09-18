OBJS = \
	ngtk-nc-base.o \
	ngtk-nc-component.o \
	ngtk-nc-container.o \
	ngtk-nc-defs.o \
	ngtk-nc-event-generator.o

all: ngtk-backend-nc.a

ngtk-backend-nc.a: $(OBJS)
	$(AR) $(ARFLAGS) ngtk-backend-nc.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
