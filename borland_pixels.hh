/* pixels.h */

#ifndef pixels_h
#define pixels_h 1

#include "public.h"

#if BORLAND
#define	BLACK	EGA_BLACK
#define WHITE	EGA_WHITE
#else
#define BLACK   0xff
#define WHITE   0x00
#endif

class pixels{
private:
  U8 far *base;		// base adress
  U32   prows;		// pixels per row
  U32	pkols;		// pixel rows on screen
  U16	pdept;		// bits per pixel ( color screens )
  U32	pcurcol;	// current pixel value (color)
public:
	pixels();
  U32	get_rows() { return prows; }
  U32   get_kols() { return pkols; }
  U16	get_depth(){ return pdept; }
  U32	get_pixel(U32 x, U32 y);
  void	set_pixel(U32 x, U32 y);
  void	xor_pixel(U32 x, U32 y);
  void  set_color(U32 c);

// line is a non virtual function and will not be overloaded by subclasses
// If the hardware or library has no line support, make it virtual!
  void	gline(U32 x1, U32 y1, U32 x2, U32 y2); //Borland C++ has a nice line()
	  				      
};

#endif
