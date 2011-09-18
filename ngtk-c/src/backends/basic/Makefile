OBJS = \
	ngtk-basic-component.o \
	ngtk-basic-container.o \
	ngtk-basic-event-generator.o

all: ngtk-backend-basic.a

ngtk-backend-basic.a: $(OBJS)
	$(AR) $(ARFLAGS) ngtk-backend-basic.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	rm *.o *.a
