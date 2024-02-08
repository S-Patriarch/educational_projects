CC=g++
CFLAGS =-c
LDFLAGS=-lmariadbclient -lpthread -lz -lm -ldl
SOURCES=main.cpp info.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tchat-server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@