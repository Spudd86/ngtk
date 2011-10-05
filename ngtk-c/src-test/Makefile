all: main.c mouse-position.c
	gcc main.c -DNGTK_USE_NC -g -lncurses -lngtk -lngtk-backend-nc -L ../src/dist/ -L ../src/backends/dist/ -o main-nc
	gcc main.c -DNGTK_USE_XLIB -g -lX11 -lngtk -lngtk-backend-xlib -L ../src/dist/ -L ../src/backends/dist/ -o main-xlib

clean:
	rm main-*

run-nc:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; ./main-nc

run-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; ./main-xlib

debug-nc:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; gdb ./main-nc

debug-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; gdb ./main-xlib

memcheck-xlib:
	export LD_LIBRARY_PATH=../src/dist:../src/backends/dist; valgrind --track-origins=yes --leak-check=full ./main-xlib
