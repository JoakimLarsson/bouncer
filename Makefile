CC=g++
CFLAGS=-c -Wall -fno-exceptions -fno-rtti
LDFLAGS=

PIXELS_SOURCES=pixels_test.cpp pixels.cpp
PIXELS_OBJECTS=$(PIXELS_SOURCES:.cpp=.o)

CROSS_SOURCES=cross_test.cpp cross.cpp
CROSS_OBJECTS=$(PIXELS_SOURCES:.cpp=.o)

GRAPHICS_SOURCES=graphics_test.cpp graphics.cpp pixels.cpp
GRAPHICS_OBJECTS=$(GRAPHICS_SOURCES:.cpp=.o)

GRAFPORT_SOURCES=grafport_test.cpp grafport.cpp pixels.cpp graphics.cpp
GRAFPORT_OBJECTS=$(GRAFPORT_SOURCES:.cpp=.o)

#$(error $(GRAFPORT_OBJECTS))

#EXECUTABLES=cross

#all: $(SOURCES) $(EXECUTABLES)

#$(EXECUTABLES): $(OBJECTS) $(HEADERS)
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

pixels: $(PIXELS_OBJECTS) public.h pixels.hh Makefile
	$(CC) $(LDFLAGS) $(PIXELS_OBJECTS) -o $@

graphics: $(GRAPHICS_OBJECTS) graphics.hh pixels.hh Makefile
	$(CC) $(LDFLAGS) $(GRAPHICS_OBJECTS) -o $@

grafport: $(GRAFPORT_OBJECTS) grafport.hh pixels.hh Makefile
	$(CC) $(LDFLAGS) $(GRAFPORT_OBJECTS) -o $@

cross: $(CROSS_OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(PIXELS_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@