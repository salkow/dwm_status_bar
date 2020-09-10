CFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations \
            -Wredundant-decls -Winline \
			-Wuninitialized -O0 -ggdb

CC = gcc
LIBS = -lX11

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

TARGET = dwm_status_bar

${TARGET}: ${OBJ}
	${CC} $(CFLAGS) ${LIBS} ${OBJ} -o ${TARGET}

main.o: main.c config.h
	${CC} $(CFLAGS) -c main.c

date.o: date.c date.h
	${CC} $(CFLAGS) -c date.c

dwmbar.o: dwmbar.c dwmbar.h
	${CC} $(CFLAGS) -c dwmbar.c

temp.o: temp.c temp.h
	${CC} $(CFLAGS) -c temp.c

updates.o: updates.c updates.h
	${CC} $(CFLAGS) -c updates.c

news.o: news.c news.h
	${CC} $(CFLAGS) -c news.c

clean:
	rm *.o ${TARGET}
