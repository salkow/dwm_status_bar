CPPFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations \
            -Wredundant-decls -Winline \
			-Wuninitialized -O0 -g

CC = g++
LIBS = -lX11 -lfmt -lasound -lxkbfile -lcurl -ljsoncpp -lmpdclient -pthread

SRCS = main.cpp status_bar.cpp item.cpp util.cpp modules/date.cpp modules/temp.cpp modules/task.cpp modules/news.cpp modules/volume.cpp modules/keyboard_language.cpp  modules/weather.cpp modules/mpd.cpp

OBJ = $(SRCS:.cpp=.o)

all: dwm_status_bar signal_status_bar

signal_status_bar.o: signal_status_bar.cpp config.hpp
	${CC} ${CPPFLAGS} -D SIGNAL -c signal_status_bar.cpp

main.o: main.cpp status_bar.o util.o
	${CC} ${CPPFLAGS} -c main.cpp

status_bar.o: status_bar.cpp status_bar.hpp item.o config.hpp
	${CC} ${CPPFLAGS} -c status_bar.cpp

item.o: item.cpp item.hpp
	${CC} ${CPPFLAGS} -c item.cpp

util.o: util.cpp util.hpp
	${CC} ${CPPFLAGS} -c util.cpp

# Modules
date.o: modules/date.cpp modules/date.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/date.cpp

temp.o: modules/temp.cpp modules/temp.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/temp.cpp

updates.o: modules/updates.cpp modules/updates.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/updates.cpp

task.o: modules/task.cpp modules/task.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/task.cpp

news.o: modules/news.cpp modules/news.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/news.cpp

volume.o: modules/volume.cpp modules/volume.hpp item.hpp
	${CC} ${CPPFLAGS} -c modules/volume.cpp

keyboard_language.o: modules/keyboard_language.cpp modules/keyboard_language.hpp
	${CC} ${CPPFLAGS} -c modules/keyboard_language.cpp 

weather.o: modules/weather.cpp modules/weather.hpp
	${CC} ${CPPFLAGS} -c modules/weather.cpp 

mpd.o: modules/mpd.cpp modules/mpd.hpp
	${CC} ${CPPFLAGS} -c modules/mpd.cpp 

dwm_status_bar: ${OBJ}
	${CC} $(CPPFLAGS) ${OBJ} -o dwm_status_bar ${LIBS} 

signal_status_bar: signal_status_bar.o
	${CC} $(CPPFLAGS) signal_status_bar.o -o signal_status_bar -D SIGNAL

clean:
	rm -f *.o modules/*.o dwm_status_bar signal_status_bar

install: dwm_status_bar signal_status_bar
	cp -f dwm_status_bar /usr/local/bin
	cp -f signal_status_bar /usr/local/bin
	chmod 755 /usr/local/bin/dwm_status_bar
	chmod 755 /usr/local/bin/signal_status_bar

uninstall:
	rm -f /usr/local/bin/dwm_status_bar
	rm -f /usr/local/bin/signal_status_bar
