include ../src/MakeConfig.mk

export NGTK_MKE=$(CC) $(CFLAGS) -g -Wall -Werror $(NGTK_CFLAGS) $(CCLDEFLAGS)
export NGTK_LD_FLAGS=

all: main.c

ifeq ($(NGTK_BUILD_NCURSES), TRUE)
	$(NGTK_MKE) -DNGTK_USE_NC *.c -lncurses -lngtk -lngtk-backend-nc -L ../src/dist/ -L ../src/backends/dist/ -o main-nc$(EXEEXT)
endif

ifeq ($(NGTK_BUILD_XLIB), TRUE)
	$(NGTK_MKE) -DNGTK_USE_XLIB *.c -lX11 -lngtk -lngtk-backend-xlib -L ../src/dist/ -L ../src/backends/dist/ -o main-xlib$(EXEEXT)
endif

ifeq ($(NGTK_BUILD_WINAPI), TRUE)
	$(NGTK_MKE) -DNGTK_USE_WINDOWS *.c -lngtk -lngtk-backend-windows -L ../src/dist/ -L ../src/backends/dist/ -o main-win$(EXEEXT)
endif

clean:
	-rm main-*

run-nc:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; ./main-nc$(EXEEXT)

run-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; ./main-xlib$(EXEEXT)

run-win:
	cp ../src/dist/*$(DLEXT) .
	cp ../src/backends/dist/*$(DLEXT) .
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; ./main-win$(EXEEXT)
	rm ./*$(DLEXT)

debug-nc:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; gdb ./main-nc

debug-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; gdb ./main-xlib

memcheck-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; valgrind --track-origins=yes --leak-check=full ./main-xlib
