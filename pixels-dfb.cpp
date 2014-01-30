/*
 * DirectFb implementation
 */

//#include <linux/fb.h>
//#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <directfb.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>

#include "public.h"

#include "pixels.hh"

#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
    							       \
    if (err != DFB_OK)                                         \
      {                                                        \
	fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
	DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;

pixels::pixels()
{
  int argc = 0;
  char **argv;
  int rows, kols;

  DFBSurfaceDescription dsc;

  DFBCHECK (DirectFBInit (&argc, &argv));
  DFBCHECK (DirectFBCreate (&dfb));
  DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));

  dsc.flags = DSDESC_CAPS;
  dsc.caps  = (DFBSurfaceCapabilities) (DSCAPS_PRIMARY | DSCAPS_FLIPPING);
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));
  DFBCHECK (primary->GetSize(primary, &kols, &rows));
  pkols = (U32) kols;
  prows = (U32) rows;

#if 0
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
  memset(base, pdept == 16 ? BLACK16 : BLACK32 , pkols * prows * pbytes);
  set_color(pdept == 16 ? WHITE16 : WHITE32);
#endif
}

pixels::~pixels()
{
#if 0
  close(fb0);
#endif
}

void pixels::set_pixel(U32 x, U32 y)
{
  /* Support for 16 bit RGB565 (RPi) boot default on HDMI */
  if (pbytes == 2){ 
    *((U8 *)(base + (pkols * y + x) * pbytes + 1)) = (pcurcol >> 8) & 0xff; 
    *((U8 *)(base + (pkols * y + x) * pbytes    )) = (pcurcol >> 0) & 0xff; 
  }
  /* Support for 32 bit RGB888 (RPi) fbset 1280x960-75-32 R&B swapped */
  else if (pbytes == 4){
    *((U8 *)(base + (pkols * y + x) * pbytes) + 2) = (pcurcol)       & 0xff; 
    *((U8 *)(base + (pkols * y + x) * pbytes) + 1) = (pcurcol >>  8) & 0xff;
    *((U8 *)(base + (pkols * y + x) * pbytes) + 0) = (pcurcol >> 16) & 0xff;
    *((U8 *)(base + (pkols * y + x) * pbytes) + 3) = (pcurcol >> 24) & 0xff;
  }
}

U32 pixels::get_pixel(U32 x, U32 y)
{
  U32 pixel;
  if (pbytes == 2){
    pixel = 
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 1)) << 8 ) |
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes)));
  }
  /* Support for 32 bit RGB888 fbset 1280x960-75-32 R&B swapped */
  else if (pbytes == 4){
    pixel = 
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 3)) << 24 ) |
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 0)) << 16 ) |
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 1)) <<  8 ) |
      (*((U8 *)(base + pkols * y * pbytes + x * pbytes + 2)) <<  0 );
  }
  /* Uknown pixel depth */
  else {
    pixel = 0xffffffff; /* -1 */
  }

  return pixel;
}

void pixels::xor_pixel(U32 x, U32 y)
{
  /* Support for 16 bit RGB565 (RPi) */
  if (pbytes == 2){ 
    *((U8 *)(base + (pkols * y + x) * pbytes + 1)) = (pcurcol >> 8) ^  get_pixel(x, y) >> 8;
    *((U8 *)(base + (pkols * y + x) * pbytes    )) = pcurcol        ^  get_pixel(x, y);
  }
  /* Support for 32 bit RGB888 fbset 1280x960-75-32 R&B swapped */
  else if (pbytes == 4){
    *((U8 *)(base + (pkols * y + x) * pbytes + 3)) = (pcurcol >> 24) ^  get_pixel(x, y) >> 24;
    *((U8 *)(base + (pkols * y + x) * pbytes + 0)) = (pcurcol >> 16) ^  get_pixel(x, y) >> 16;
    *((U8 *)(base + (pkols * y + x) * pbytes + 1)) = (pcurcol >>  8) ^  get_pixel(x, y) >>  8;
    *((U8 *)(base + (pkols * y + x) * pbytes + 2)) = (pcurcol >>  0) ^  get_pixel(x, y);
  }
}

void  pixels::set_color(U32 c)
{
  switch (c){
  case RED:   pcurcol = pbytes == 2 ? RED16   : RED32; break;
  case GREEN: pcurcol = pbytes == 2 ? GREEN16 : GREEN32; break;
  case BLUE:  pcurcol = pbytes == 2 ? BLUE16 : BLUE32; break;
  case WHITE: pcurcol = pbytes == 2 ? WHITE16 : WHITE32; break;
  case BLACK: // - fall though to default
  default:    pcurcol = pbytes == 2 ? BLACK16 : BLACK32; 
  }
}

