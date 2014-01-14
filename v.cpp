#include <stdio.h>

#include "public.h"
#include "viewer.hh"

#if BORLAND
#include "graphics.h"
#endif

#define QBSIZE (100<<4)		// viewer volume qube side definition

#define setXY(x, y) putpixel(x, y, EGA_WHITE);

void myline(int x1, int y1, int x2, int y2)
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
    setXY(x, y);
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
      setXY(x, y);
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
    setXY(x, y);
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
      setXY(x, y);
    }
  }
}

void viewer::draw(int erase)
{
#if BORLAND
  if ( erase==TRUE )
    setcolor(EGA_BLACK);
  else
    setcolor(EGA_WHITE);
#endif

#if 0
  pline(   0,   0,   0,   0, QBSIZE,   0);
  pline(   0, QBSIZE,   0, QBSIZE, QBSIZE,   0);
  pline( QBSIZE, QBSIZE,   0, QBSIZE,   0,   0);
  pline( QBSIZE,   0,   0,   0,   0,   0);

  pline(   0,   0, QBSIZE,   0, QBSIZE, QBSIZE);
  pline(   0, QBSIZE, QBSIZE, QBSIZE, QBSIZE, QBSIZE);
  pline( QBSIZE, QBSIZE, QBSIZE, QBSIZE,   0, QBSIZE);
  pline( QBSIZE,   0, QBSIZE,   0,   0, QBSIZE);
#endif

}


void viewer::calc_const()
{
// pre calculation of some commonly used constants
  dVx = Vx2 - Vx1;
  dVy = Vz2 - Vz1;
  dVz = Vz2 - Vz1;
  dTx = Tx2 - Tx1;
  dTy = Ty2 - Ty1;
}


viewer::viewer()
{
  Vx1 = Vy1 = Vz1 = 0;
  Vx2 = QBSIZE;  Vy2 = QBSIZE;  Vz2 = QBSIZE;
  Tx1 = 48<<4;   Tx2 = 52<<4;
  Ty1 = 48<<4;   Ty2 = 52<<4;

  Sx1 = 100;	Sy1 = 40;
  Sx2 = 500;	Sy2 = 440;

  reduct = 3;
  calc_const();
  draw(FALSE);
 
#if BORLAND				// manages offset and clipping
  setviewport(Sx1, Sy1, Sx2, Sy2, TRUE);
#endif

};

void viewer::inc_zoom()
{
  reduct++;
}

void viewer::dec_zoom()
{
  reduct--;
}

void viewer::pline(S32 x1, S32 y1, S32 z1, S32 x2, S32 y2, S32 z2)
{
  S32 Tx, Ty;			// projection point at view angle rectangle
  S32 Px1, Py1, Px2, Py2;	// Projected line, 3D -> 2D
  S32 Vx, Vy, Vz;
  S32 t1,t2,t3;

#if 0
  printf("HEX pline(%08lx %08lx %08lx %08lx %08lx %08lx\n",
  	 x1, y1, z1, x2, y2, z2);
  printf("DEC pline(%08lu %08lu %08lu %08lu %08lu %08lu => \n",
  	 x1, y1, z1, x2, y2, z2);
#endif

//  x1 -= Vx1; y1 -= Vy1; z1 -= Vz1;
//  x2 -= Vx2; y2 -= Vy2; z2 -= Vz2;

  Tx = (x1 * dTx)/dVx + Tx1;
  Ty = (y1 * dTy)/dVy + Ty1;

//  Px1 = ((Tx - x1) * z1)/dVz + x1;
  Px1 = ((Tx - x1) * (z1 - Vz1))/dVz + x1 - Vx1;
//  Py1 = ((Ty - y1) * z1)/dVz + y1;
  Py1 = ((Ty - y1) * (z1 - Vz1))/dVz + y1 - Vy1;

  Tx = (x2 * dTx)/dVx + Tx1;
  Ty = (y2 * dTy)/dVy + Ty1;

//  Px2 = ((Tx - x2) * z2)/dVz + x2;
  Px2 = ((Tx - x2) * (z2 - Vz1))/dVz + x2 - Vx1;
//  Py2 = ((Ty - y2) * z2)/dVz + y2;
  Py2 = ((Ty - y2) * (z2 - Vz1))/dVz + y2 - Vy1;

  myline(Px1 >> reduct,
       Py1 >> reduct,
       Px2 >> reduct,
       Py2 >> reduct);

#if 0
  printf("HEX line(%08lx %08lx %08lx %08lx, %08lx %08lx\n",
  	  Px1, Py1, 0L, Px2, Py2, 0L);
  printf("DEC line(%08lu %08lu %08lu %08lu, %08lu %08lu\n\n",
  	  Px1, Py1, 0L, Px2, Py2, 0L);
#endif
}
