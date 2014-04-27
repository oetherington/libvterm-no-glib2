CFLAGS = -Wall -O2 -std=gnu99
DEFS = -D_REENTRANT
prefix = /usr/local
libdir = /usr/lib
includedir = /usr/include

makefile: all

all: libvterm

debug: libvterm

libvterm:
	gcc $(CFLAGS) $(DEFS) -c -fPIC *.c
	gcc -shared -o libvterm.so -lutil *.o

clean:
	rm -f *.o
	rm -f *.so

install:
	cp -f vterm.h $(includedir)
	cp -f libvterm.so $(libdir)
	chmod 755 /usr/lib/libvterm.so
	ldconfig


