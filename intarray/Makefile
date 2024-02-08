CC=g++
CFLAGS =-c
LDFLAGS=
SOURCES=main.cpp intarray.cpp pconio.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=intarray

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@