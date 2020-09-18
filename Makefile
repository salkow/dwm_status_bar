CPPFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations \
            -Wredundant-decls -Winline \
			-Wuninitialized -O0 -ggdb

CC = g++
LIBS = -lX11 -lfmt

SRCS = $(wildcard *.cpp) $(wildcard modules/*.cpp)

OBJ = $(SRCS:.cpp=.o)

TARGET = dwm_status_bar

${TARGET}: ${OBJ} ${OBJJ}
	${CC} $(CPPFLAGS) ${LIBS} ${OBJ} -o ${TARGET}

main.o: main.cpp status_bar.hpp
	${CC} $(CPPFLAGS) -c main.cpp

status_bar.o: status_bar.cpp status_bar.hpp config.hpp item.hpp
	${CC} $(CPPFLAGS) -c status_bar.cpp

# Modules
date.o: modules/date.cpp modules/date.hpp item.hpp
	${CC} $(CPPFLAGS) -c modules/date.cpp

temp.o: modules/temp.cpp modules/temp.hpp item.hpp
	${CC} $(CPPFLAGS) -c modules/temp.cpp

updates.o: modules/updates.cpp modules/updates.hpp item.hpp
	${CC} $(CPPFLAGS) -c modules/updates.cpp

news.o: modules/news.cpp modules/news.hpp item.hpp
	${CC} $(CPPFLAGS) -c modules/news.cpp

clean:
	rm *.o modules/*.o ${TARGET}

