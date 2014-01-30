CC=g++
CFLAGS=-c -Wall -fno-exceptions -fno-rtti
LDFLAGS=

PIXELS_SOURCES=pixels_test.cpp pixels-fb.cpp
PIXELS_OBJECTS=$(PIXELS_SOURCES:.cpp=.o)

GRAPHICS_SOURCES=graphics_test.cpp graphics.cpp pixels-fb.cpp
GRAPHICS_OBJECTS=$(GRAPHICS_SOURCES:.cpp=.o)

GRAFPORT_SOURCES=grafport_test.cpp grafport.cpp pixels-fb.cpp graphics.cpp
GRAFPORT_OBJECTS=$(GRAFPORT_SOURCES:.cpp=.o)

CROSS_SOURCES=cross_test.cpp cross.cpp pixels-fb.cpp graphics.cpp viewer.cpp mover.cpp grafport.cpp bouncer.cpp
CROSS_OBJECTS=$(CROSS_SOURCES:.cpp=.o)

BOUNCER_SOURCES=bouncer_test.cpp bouncer.cpp pixels-fb.cpp graphics.cpp viewer.cpp mover.cpp grafport.cpp
BOUNCER_OBJECTS=$(BOUNCER_SOURCES:.cpp=.o)

VIEWER_SOURCES=viewer_test.cpp viewer.cpp
VIEWER_OBJECTS=$(VIEWER_SOURCES:.cpp=.o)

MOVER_SOURCES=mover_test.cpp mover.cpp
MOVER_OBJECTS=$(MOVER_SOURCES:.cpp=.o)

CLEAN_LIST = $(PIXELS_OBJECTS) $(CROSS_OBJECTS) $(VIEWER_OBJECTS) $(GRAPHICS_OBJECTS) $(GRAFPORT_OBJECTS) $(MOVER_OBJECTS)

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

cross: $(CROSS_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(LDFLAGS) $(CROSS_OBJECTS) -o $@

bouncer: $(BOUNCER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(LDFLAGS) $(BOUNCER_OBJECTS) -o $@

viewer: $(VIEWER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(LDFLAGS) $(VIEWER_OBJECTS) -o $@

mover: $(MOVER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(LDFLAGS) $(MOVER_OBJECTS) -o $@

clean:
	@- $(RM) $(CLEAN_LIST)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@