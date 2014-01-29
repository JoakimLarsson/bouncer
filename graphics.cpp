#include <stdio.h>
#include <stdlib.h>

#include "public.h"

#include "pixels.hh"
#include "graphics.hh"

void graphics::gline(U32 x1, U32 y1, U32 x2, U32 y2)
{
  S16 dx,dy,p,const1, const2, x, y, sign, end;

#if DEBUG
  fprintf(debugio, "gline: %6d %6d %6d %6d \n", x1, y1, x2, y2);
#endif

  dx = x1 - x2; dx = dx < 0 ? -dx : dx;
  dy = y1 - y2; dy = dy < 0 ? -dy : dy;

  if (dx > dy){
    if (x1 > x2){
      x = x2; x2 = x1; x1 = x;
      y = y2; y2 = y1; y1 = y;
    }
    else{
      x = x1;
      y = y1;
    }
    set_pixel(x, y);
    end = x2;
    sign = y2 < y1 ? -1 : 1;
    p = 2 * dy - dx;
    const1 = 2 * dy;
    const2 = 2 * (dy - dx);
    while (x < end){
      x++;
      if (p < 0)
	p += const1;
      else{
	y += sign;
	p += const2;
      }
      set_pixel(x, y);
    }
  }
  else{
    if (y1 > y2){
      x = x2; x2 = x1; x1 = x;
      y = y2; y2 = y1; y1 = y;
    }
    else{
      x = x1;
      y = y1;
    }
    set_pixel(x, y);
    end = y2;
    sign = x2 < x1 ? -1 : 1;
    p = 2 * dx - dy;
    const1 = 2 * dx;
    const2 = 2 * (dx - dy);
    while (y < end){
      y++;
      if (p < 0)
	p += const1;
      else{
	x += sign;
	p += const2;
      }
      set_pixel(x, y);
    }
  }
}

#if 0
main()
{
  class graphics *grf;
  int i,j;
  int ErrorCode;
  int GraphMode;
  int GraphDriver = DETECT; 		/* Request auto-detection	*/

  grf = new graphics;


#if 1
  initgraph( &GraphDriver, &GraphMode, "" );
  ErrorCode = graphresult();		/* Read result of initialization*/
  if( ErrorCode != grOk ){		/* Error occured during init	*/
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );

    exit( 1 );
  }
#endif

  grf -> line( (U32)10, (U32)10, (U32)34, (U32)34 );
  grf -> line( (U32)10, (U32)10, (U32)44, (U32)44 );

  for(i = 0; i < 10000; i)
    putchar('\r');


#if 0
  asm push	ax
  asm mov	ax,0
  asm mov       al,011h
  asm int	010h
  asm pop 	ax
#endif
#if 0
  for (i = 0; i <= 8; i++){
    asm	push	ax
    asm	push	dx
    asm	mov	ax,3ceh
    asm	mov	dx,ax
    asm	mov	ax,i
    asm	out	dx,al
    asm	inc	dx
    asm mov	ax,0
    asm	in	al,dx
    asm mov	j,ax
    asm	pop	dx
    asm	pop	ax

    printf("Reg %d = %02x \n",i ,j);
  }
  putpixel(200, 200, EGA_WHITE);
  line(110, 10, 150, 50);
#endif
#if 0
  asm push	ax
  asm push	bx
  asm push	cx
  asm push	dx

  asm mov	ah,0ch
  asm mov       al,0ffh
  asm mov	bh,0
  asm mov	cx,064h
  asm mov	dx,064h
  asm int	010h

  asm push	ds
  asm push	si
  asm mov	ax,0a000h
  asm mov	ds,ax
  asm mov	si,01f40h

  asm mov	ax,03ceh	// Enable Set Res 15
  asm mov	dx,ax
  asm mov	al,1
  asm out	dx,al
  asm inc	dx
  asm mov	al,0fh
  asm out	dx,al

  asm mov	ax,03ceh	// Set Res 1
  asm mov	dx,ax
  asm mov	al,0
  asm out	dx,al
  asm inc	dx
  asm mov	al,01h
  asm out	dx,al

  asm mov	al,ds:[si]	// /* dummy read */
  asm mov	ds:[si],al

  asm pop	si
  asm pop	ds

  asm pop	dx
  asm pop	cx
  asm pop	bx
  asm pop 	ax
#endif

#if 0
  *((char far *) 0xa0000) = 0xff;
  *((char far *) 0xa0100) = 0xff;
  *((char far *) 0xa0200) = 0xff;
#endif

}
#endif
