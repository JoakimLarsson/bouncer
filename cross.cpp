#include <stdio.h>

#include "public.h"

#if BORLAND
#include <conio.h>
#endif

#include "pixels.hh"
#include "grafport.hh"
#include "mover.hh"
#include "cross.hh"
#include "bouncer.hh"
#include "viewer.hh"

static line3Dtype clines[] = {

  {-RAD, -RAD,    0,  RAD,  RAD,    0},
  {-RAD,  RAD,    0,  RAD, -RAD,    0},
  {    0,    0, -RAD,    0,    0,  RAD} };

cross::cross(class viewer *v)
{
  int i;

  view = v;

  for (i=0; i < 3; i++){		// define dummy line for first
    lin[i].sx1 =		// erase of 2D line
    lin[i].sy1 =
    lin[i].sx2 =
    lin[i].sy2 = (S16) 0;
    curlines[i] = clines[i];
  }
  curang = 90;
};

void cross::erase()
{
  int i;

  (view->grf) -> set_color((U32)BLACK);
  for (i = 0; i < 3; i++){
    ((class grafport *)(view->grf)) -> pline( lin[i].sx1, lin[i].sy1,	// erase old lines
                          lin[i].sx2, lin[i].sy2 );

    lin[i].sx1 = lin[i].sy1 = lin[i].sx2 = lin[i].sy2 = (S16) 0;
  }
}


void cross::draw()
{
  int i;
  S32 xprim, yprim;

  curang = (curang + 1) % 360;

  // Initialize from const cross objects
  for(i = 0; i < 3; i++)
    curlines[i] = clines[i];

  // Draw each line
  for (i = 0; i < 3; i++){
    lin[i].line3D = curlines[i];
    (view->grf) -> set_color(color);
    mline(&lin[i]);
  }
}
