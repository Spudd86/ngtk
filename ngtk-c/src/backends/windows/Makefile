OBJS = \
	ngtk-widget-window.c \
	ngtk-win-base.c \
	ngtk-win-component.c \
	ngtk-win-container.c \
	ngtk-win-defs.c \
	ngtk-win-event-generator.c

all: libngtk-backend-windows.a

libngtk-backend-windows.a: $(OBJS)
	$(NGTK_MKS) libngtk-backend-windows.a $(OBJS)

%.o: %.c
	$(CC) -c $<

clean:
	find "(" -regex ".*\.o" -or -regex ".*\.a" ")" -delete
