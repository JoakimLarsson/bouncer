CC=g++
CFLAGS=-c -Wall -fno-exceptions -fno-rtti
LDFLAGS=
HEADERS=public.h pixels.hh
SOURCES=pixels_test.cpp pixels.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pixels

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@