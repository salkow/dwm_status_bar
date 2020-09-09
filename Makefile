CFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations \
            -Wredundant-decls -Winline \
            -Wuninitialized -g -lX11

all: main.o date.o dwmbar.o temp.o updates.o news.o
	gcc $(CFLAGS) -o dwm_status_bar main.o date.o dwmbar.o temp.o updates.o news.o

main.o: main.c config.h
	gcc $(CFLAGS) -c main.c

date.o: date.c date.h
	gcc $(CFLAGS) -c date.c

dwmbar.o: dwmbar.c dwmbar.h
	gcc $(CFLAGS) -c dwmbar.c

temp.o: temp.c temp.h
	gcc $(CFLAGS) -c temp.c

updates.o: updates.c updates.h
	gcc $(CFLAGS) -c updates.c

news.o: news.c news.h
	gcc $(CFLAGS) -c news.c
