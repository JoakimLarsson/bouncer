CC=g++
CFLAGS=-c -Wall -fno-exceptions -fno-rtti
LDFLAGS=

HEADERS=public.h pixels.hh

PIXELS_SOURCES=pixels_test.cpp pixels.cpp
SOURCES=$(PIXELS_SOURCES)

PIXELS_OBJECTS=$(PIXELS_SOURCES:.cpp=.o)
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=cross

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

pixels: $(PIXELS_OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(PIXELS_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@