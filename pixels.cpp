#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "public.h"

#include "pixels.hh"

pixels::pixels()
{
  struct fb_var_screeninfo fb_info; /* info structure for framebuffer */

  if ((fb0 = open("/dev/fb0", O_RDWR)) == -1){
    printf("Can't open framebuffer\n");
    exit(1);
  }
  if (ioctl(fb0, FBIOGET_VSCREENINFO, &fb_info) != 0){
    printf("Can't get resolution\n");
    exit(1);
  }
  prows = fb_info.yres;
  pkols = fb_info.xres;
  pdept = fb_info.bits_per_pixel;
  pbytes = pdept / 8;
  base = (U8 *) mmap(NULL, pkols * prows * pbytes, PROT_WRITE | PROT_READ, MAP_SHARED, fb0, 0);
  
  /* clear display */
  memset(base, BLACK, pkols * prows * pbytes);
  set_color(WHITE);
}

pixels::~pixels()
{
  close(fb0);
}

void pixels::set_pixel(U32 x, U32 y)
{
  /* Support for 16 bit RGB565 (RPi) */
  if (pbytes == 2){ 
    *((U8 *)(base + (pkols * y + x) * pbytes + 1)) = (pcurcol >> 8) & 0xff; 
    *((U8 *)(base + (pkols * y + x) * pbytes    )) = (pcurcol >> 0) & 0xff; 
  }
}

U32 pixels::get_pixel(U32 x, U32 y)
{
  return ( U32 ) 
    (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 1)) << 8 ) |
    (*((U8 *)(base + pkols * y * pbytes + x * pbytes)));
}

void pixels::xor_pixel(U32 x, U32 y)
{
  /* Support for 16 bit RGB565 (RPi) */
  if (pbytes == 2){ 
    memset(base + pbytes * x + pbytes * pkols * y, 
	   pcurcol        ^  get_pixel(x, y), 1);
    memset(base + pbytes * x + pbytes * pkols * y + 1, 
	   (pcurcol >> 8) ^ (get_pixel(x, y) >> 8), 1);
  }
}

void  pixels::set_color(U32 c)
{
  pcurcol = (U32) c;
}

void pixels::line(U32 x1, U32 y1, U32 x2, U32 y2)
{
  int dx,dy,p,const1, const2, x, y, sign, end;

  dx = abs(x1 - x2);
  dy = abs(y1 - y2);

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
