CC=g++
CFLAGS =-c
LDFLAGS=
SOURCES=main.cpp info.cpp file.cpp user.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tchat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@