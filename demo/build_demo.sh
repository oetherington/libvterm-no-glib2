#!/bin/sh
gcc -o vshell -lvterm -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -lncurses -ltinfo *.c -ggdb3 -lglib-2.0
