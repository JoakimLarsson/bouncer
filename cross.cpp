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

static line3Dtype lines[] = {

    -RAD, -RAD,    0,  RAD,  RAD,    0,
    -RAD,  RAD,    0,  RAD, -RAD,    0,
       0,    0, -RAD,    0,    0,  RAD };

cross::cross(class viewer *v)
{
  int i;

  view = v;

  for (i=0; i < 3; i++){		// define dummy line for first
    lin[i].sx1 =		// erase of 2D line
    lin[i].sy1 =
    lin[i].sx2 =
    lin[i].sy2 = (S16) 0;
    curlines[i] = lines[i];
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

  for(i = 0; i < 3; i++)
    curlines[i] = lines[i];

#if 0
  for  (i = 0; i < 2; i++){
    xprim = curlines[i].x1 * cos(curang) -
    	    curlines[i].y1 * sin(curang);
    yprim = curlines[i].y1 * cos(curang) +
    	    curlines[i].x1 * sin(curang);
    curlines[i].x1 = xprim;
    curlines[i].y1 = yprim;
    xprim = curlines[i].x2 * cos(curang) -
    	    curlines[i].y2 * sin(curang);
    yprim = curlines[i].y2 * cos(curang) +
    	    curlines[i].x2 * sin(curang);
    curlines[i].x2 = xprim;
    curlines[i].y2 = yprim;
  }
#endif

  for (i = 0; i < 3; i++){
    lin[i].line3D = curlines[i];
    mline(&lin[i]);
//    getch();
  }
}
