#include <stdio.h>
#include <stdlib.h>

#include "public.h"

#include "pixels.hh"

pixels::pixels()
{
#if BORLAND
//
// Borland C++ specifics
//
  int ErrorCode;
  int GraphMode;
  int GraphDriver = DETECT; 		/* Request auto-detection	*/

  initgraph( &GraphDriver, &GraphMode, "" );
  ErrorCode = graphresult();		// Read result of initialization
  if( ErrorCode != grOk ){		// Error occured during init	
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );

    exit( 1 );
  }
  setwritemode(XOR_PUT); // causes the line function to XOR onto screen
#endif

  setcolor(WHITE);
  base 	= (U8 far *) 0xa0000;	// baseadress of screen;
  prows = 1000;
  pkols = 1000;
  pdept = 1;
}

U32 pixels::get_pixel(U32 x, U32 y)
{
#if BORLAND
  return ( U32 ) getpixel( (int) x, (int) y);
#endif
}

void pixels::set_pixel(U32 x, U32 y)
{
#if BORLAND
  putpixel( (int) x, (int) y, (int) pcurcol);
#endif
}

void pixels::xor_pixel(U32 x, U32 y)
{
#if BORLAND
  putpixel( (int) x, (int) y, (int) getpixel((int) x, (int) y) ^ EGA_WHITE);
#endif
}

void  pixels::set_color(U32 c)
{
  pcurcol = (U32) c;
}

void pixels::gline(U32 x1, U32 y1, U32 x2, U32 y2)
{

#if DEBUG
  fprintf(debugio, "pline: %6ld %6ld %6ld %6ld \n", x1, y1, x2, y2);
#endif

#if BORLAND
  line( (int) x1, (int) y1, (int) x2, (int) y2);
#endif
}
