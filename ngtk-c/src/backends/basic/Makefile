OBJS = \
	ngtk-basic-base.o \
	ngtk-basic-backend.o \
	ngtk-basic-component.o \
	ngtk-basic-container.o

all: libngtk-backend-basic.a

libngtk-backend-basic.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-basic.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
