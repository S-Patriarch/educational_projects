CC=g++
CFLAGS =-c
LDFLAGS=
SOURCES=main.cpp info.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tchat-client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@