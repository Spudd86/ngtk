OBJS = \
	ngtk-basic-base.o \
	ngtk-basic-backend.o \
	ngtk-basic-component.o \
	ngtk-basic-container.o \
	ngtk-basic-graphics.o \
	ngtk-basic-text-entry.o

all: libngtk-backend-basic.a

libngtk-backend-basic.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-basic.a $(OBJS)

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a