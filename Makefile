
# Device specific implementation, enable just one
PIXELS=pixels-fb.cpp
#PIXELS=pixels-dfb.cpp
#PIXELS_CFLAGS=-I/usr/include/directfb
#PIXELS_LDFLAGS=-ldirectfb

CC=g++
CFLAGS=-c -Wall -fno-exceptions -fno-rtti $(PIXELS_CFLAGS)
LDFLAGS= $(PIXELS_LDFLAGS)

PIXELS_SOURCES=pixels_test.cpp $(PIXELS)
PIXELS_OBJECTS=$(PIXELS_SOURCES:.cpp=.o)

GRAPHICS_SOURCES=graphics_test.cpp graphics.cpp $(PIXELS)
GRAPHICS_OBJECTS=$(GRAPHICS_SOURCES:.cpp=.o)

GRAFPORT_SOURCES=grafport_test.cpp grafport.cpp $(PIXELS) graphics.cpp
GRAFPORT_OBJECTS=$(GRAFPORT_SOURCES:.cpp=.o)

CROSS_SOURCES=cross_test.cpp cross.cpp $(PIXELS) graphics.cpp viewer.cpp mover.cpp grafport.cpp bouncer.cpp
CROSS_OBJECTS=$(CROSS_SOURCES:.cpp=.o)

BOUNCER_SOURCES=bouncer_test.cpp bouncer.cpp $(PIXELS) graphics.cpp viewer.cpp mover.cpp grafport.cpp
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
#	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

pixels: $(PIXELS_OBJECTS) public.h pixels.hh Makefile
	$(CC) $(PIXELS_OBJECTS) -o $@ $(LDFLAGS) 

graphics: $(GRAPHICS_OBJECTS) graphics.hh pixels.hh Makefile
	$(CC) $(GRAPHICS_OBJECTS) -o $@ $(LDFLAGS) 

grafport: $(GRAFPORT_OBJECTS) grafport.hh pixels.hh Makefile
	$(CC) $(GRAFPORT_OBJECTS) -o $@ $(LDFLAGS) 

cross: $(CROSS_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(CROSS_OBJECTS) -o $@ $(LDFLAGS) 

bouncer: $(BOUNCER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(BOUNCER_OBJECTS) -o $@ $(LDFLAGS) 

viewer: $(VIEWER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(VIEWER_OBJECTS) -o $@ $(LDFLAGS) 

mover: $(MOVER_OBJECTS) $(HEADERS) public.h Makefile
	$(CC) $(MOVER_OBJECTS) -o $@ $(LDFLAGS) 

clean:
	@- $(RM) $(CLEAN_LIST)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@