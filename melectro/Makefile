CC=g++
CFLAGS =-c
LDFLAGS=
SOURCES=main.cpp pconio.cpp applianc.cpp pelectro.cpp mixed.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=melectro

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@