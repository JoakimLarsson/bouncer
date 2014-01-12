Bouncer
=======

A really low level 3D simulation of "balls" bouncing in boxes. Yes I did one too. :-)

The project started out on my Macintosh SE somewhere around 1989 using Think C which 
had object oriented extensions and a 1 bit framebuffer with direct memoryaccess. 
The idea was to see what performance was possible on the Macintosh with its 7.8MHz 
68000 CPU, so all routines were written by hand using no compiler libraries.

Some years later around 1994 I ported it over to Borland C++ and in fact used the 
build in library functions for pixel access and draw lines. I also extended it to be 
instantiable for multiple 3D boxes and for a while I used it as a dream box stairing
at the balls trying to find patterns in the simulation. I experiemented with setting
the speed and direction of the balls according to different algorithms and also 
implemented pause functions, single step and reverse. I guess I was understimulated
during this time of my life.

Now, I am going back to the native implementation for Raspberry Pi and while not
understimulated myself anymore I want to share this code on GitHub for others to 
ponder. I also need to refresh my C++ skills a bit so this is the way I choose to do it.

Joakim Larsson
