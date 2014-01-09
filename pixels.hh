/* pixels.h */

#ifndef pixels_h
#define pixels_h 1

#include "public.h"

class pixels{
private:
  U8 far *base;		// base adress
  U32   prows;		// pixels per row
  U32	pkols;		// pixel rows on screen
  U16	pdept;		// bits per pixel ( color screens )
  U32	pcurcol;	// current pixel value (color)
public:
	pixels();
	~pixels();
  U32	get_rows() { return prows; }
  U32   get_kols() { return pkols; }
  U16	get_depth(){ return pdept; }
  U32	get_pixel(U32 x, U32 y);
  void	set_pixel(U32 x, U32 y);
  void	xor_pixel(U32 x, U32 y);
  void  set_color(U32 c);
  void	line(U32 x1, U32 y1, U32 x2, U32 y2);
	  				      
};

#endif
