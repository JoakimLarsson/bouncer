/* pixels.h */

#ifndef pixels_h
#define pixels_h 1

#include "public.h"

#define WHITE 1
#define BLACK 2
#define RED   3
#define GREEN 4
#define BLUE  5


/* 16 bit RGB565 colors */
#define WHITE16 0x0000ffff
#define BLACK16 0x00000000
#define RED16   0x0000f800
#define GREEN16 0x000007e0
#define BLUE16  0x0000001f

/* 32 bit RGB888 colors */
#define WHITE32 0xffffffff
#define BLACK32 0xff000000
#define RED32   0xffff0000
#define GREEN32 0xff00ff00
#define BLUE32  0xff0000ff

class pixels{
private:
  U8    *base;		// base adress
  U32   prows;		// pixels per row
  U32	pkols;		// pixel rows on screen
  U16	pdept;		// bits per pixel ( color screens )
  U16   pbytes;         // bytes per pixel
  U32	pcurcol;	// current pixel value (color)
  int  fb0;            /* framebuffer decriptor */
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
