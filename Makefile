CPPFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations \
            -Wredundant-decls -Winline \
			-Wuninitialized -pthread -O0 -g

CC = g++
LIBS = -lX11 -lfmt -lasound -lxkbfile -lcurl -ljsoncpp -lmpdclient

SRCS = $(wildcard *.cpp) $(wildcard modules/*.cpp)

OBJ = $(SRCS:.cpp=.o)

TARGET = dwm_status_bar

${TARGET}: ${OBJ}
	${CC} $(CPPFLAGS) ${LIBS} ${OBJ} -o ${TARGET}

main.o: main.cpp status_bar.o util.o
	${CC} -c main.cpp

status_bar.o: status_bar.cpp status_bar.hpp item.o config.hpp
	${CC} -c status_bar.cpp

item.o: item.cpp item.hpp
	${CC} -c item.cpp

util.o: util.cpp util.hpp
	${CC} -c util.cpp

# config.o: config.cpp item.hpp
# 	${CC} -c config.cpp

# Modules
date.o: modules/date.cpp modules/date.hpp item.hpp
	$(CC) -c modules/date.cpp

temp.o: modules/temp.cpp modules/temp.hpp item.hpp
	$(CC) -c modules/temp.cpp

updates.o: modules/updates.cpp modules/updates.hpp item.hpp
	$(CC) -c modules/updates.cpp

task.o: modules/task.cpp modules/task.hpp item.hpp
	$(CC) -c modules/task.cpp

news.o: modules/news.cpp modules/news.hpp item.hpp
	$(CC) -c modules/news.cpp

volume.o: modules/volume.cpp modules/volume.hpp item.hpp
	$(CC) -c modules/volume.cpp

keyboard_language.o: modules/keyboard_language.cpp modules/keyboard_language.hpp
	$(CC) -c modules/keyboard_language.cpp 

weather.o: modules/weather.cpp modules/weather.hpp
	$(CC) -c modules/weather.cpp 

mpd.o: modules/mpd.cpp modules/mpd.hpp
	$(CC) -c modules/mpd.cpp 

clean:
	rm -f *.o modules/*.o ${TARGET}

install: ${TARGET}
	cp -f dwm_status_bar /usr/local/bin
	chmod 755 /usr/local/bin/dwm_status_bar

uninstall:
	rm -f /usr/local/bin/dwm_status_bar
