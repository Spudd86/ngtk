OBJS = \
	ngtk-win-backend.o \
	ngtk-win-component.o \
	ngtk-win-container.o \
	ngtk-win-defs.o \
	ngtk-win-window.o

all: libngtk-backend-windows.a

libngtk-backend-windows.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-windows.a $(OBJS)

%.o: %.c %.h
	$(NGTK_MKO) -c $< -o $@

clean:
	-rm *.o *.a