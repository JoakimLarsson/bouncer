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

#if DEBUG
  fprintf(debugio, "pline: %6ld %6ld %6ld %6ld \n", x1, y1, x2, y2);
#endif

#if BORLAND
  line( (int) x1, (int) y1, (int) x2, (int) y2);
#endif
}
