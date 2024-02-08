CC=g++
CFLAGS =-c
LDFLAGS=
SOURCES=main.cpp chat.cpp sha1.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hashtable

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@