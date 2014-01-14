#include <stdio.h>
#include <stdlib.h>

#include "public.h"

#include "viewer.hh"
#include "graphics.hh"
#include "grafport.hh"
#include "pixels.hh"


#define QBSIZE (250<<4)		// viewer volume qube side definition


void viewer::calc_const()
{
// pre calculation of some commonly used constants
  dVx = Vx2 - Vx1;
  dVy = Vy2 - Vy1;
  dVz = Vz2 - Vz1;
  dTx = Tx2 - Tx1;
  dTy = Ty2 - Ty1;
}


viewer::viewer(class grafport *g)
{
  grf = g; // graphics class interface to display hardware

  set_position(1015, 1015, 1000);

  Vx1 = Vy1 = -1 * (QBSIZE >> 1);
  Vx2 = Vy2 = QBSIZE >> 1;
  Vz1 = 0; Vz2 = QBSIZE;

  Tx1 = Ty1 = -1 * (10 << 4);
  Tx2 = Ty2 = 10 << 4;

  Sx1 = Sy1 = Sx2 = Sy2 = 0;

  calc_const();
};

void viewer::clip_min( line3Dtype *lin, S32 minZ)
{
}

void viewer::clip_max( line3Dtype *lin, S32 maxZ )
{
}

int viewer::clipZ( line3Dtype *lin )
{
  S32 minZ, maxZ;
  U16 mask;
  int ret;

  maxZ = Vz1 + 9 * (dVz * dVx) / (10 * (dVx - dTx)); // 90 % of dist to COP
  minZ = Vz1 + maxZ / 10;			     // 10 % of maxZ

  if (lin->z1 >= maxZ)	    mask = 4;
  else if (lin->z1 <= minZ) mask = 1;
  else			    mask = 2;

  if (lin->z2 >= maxZ)	    mask |= 4;
  else if (lin->z2 <= minZ) mask |= 1;
  else			    mask |= 2;

#if DEBUG
  fprintf(debugio, "clipZ: %02x\n", mask);
#endif

  switch ((int) mask){
  case 2 	: ret = 0; break;	// whole line between minZ and maxZ
  case 1	:
  case 4 	: ret = 1; break;	// whole line outside minZ and maxZ
  case 3	: clip_min(lin, minZ);
  		  ret = 0; break;
  case 5	: clip_min(lin, minZ);
  		  clip_max(lin, maxZ);
		  ret = 0; break;
  case 6	: clip_max(lin, maxZ);
  		  ret = 0; break;
  default	: printf("Error in Z clip\n");
  		  exit(1);
  }
  return ret;
}

void viewer::vline(linetype *lin)
{
  S32 Tx, Ty;			// projection point at view angle rectangle
  S32 Px1, Py1, Px2, Py2;	// Projected line, 3D -> 2D
  S32 tmp, x, y, z;
  line3Dtype line3D;

#if DEBUG
  fprintf(debugio, "vline: %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f\n",
  ((float) lin->line3D.x1)/16, ((float) lin->line3D.y1)/16, 
  ((float) lin->line3D.z1)/16, ((float) lin->line3D.x2)/16,
  ((float) lin->line3D.y2)/16, ((float) lin->line3D.z2)/16 );
#endif

  line3D = lin -> line3D;
  tmp = get_px(); line3D.x1 -= tmp; line3D.x2 -= tmp;
  tmp = get_py(); line3D.y1 -= tmp; line3D.y2 -= tmp;
  tmp = get_pz(); line3D.z1 -= tmp; line3D.z2 -= tmp;

#if DEBUG
  fprintf(debugio, "vline2: %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f\n",
  ((float) line3D.x1)/16, ((float) line3D.y1)/16, 
  ((float) line3D.z1)/16, ((float) line3D.x2)/16,
  ((float) line3D.y2)/16, ((float) line3D.z2)/16 );
#endif

#if 0
  if (clipZ(&line3D)){
    grf -> set_color((U32)BLACK);
    ((class pixels *)grf) -> gline(lin->sx1, lin->sy1,	// erase old line
	                           lin->sx2, lin->sy2 );
    return;
  }
#endif

// Calculate new line
  x = line3D.x1;
  y = line3D.y1;
  z = line3D.z1;

  Tx = (x * dTx)/dVx + Tx1 ;
  Ty = (y * dTy)/dVy + Ty1 ;

//  Px1 = ( ((Tx - x ) * (z - Vz1) ) / dVz + x - Vx1 ) >> 2;
//  Py1 = ( ((Ty - y ) * (z - Vz1) ) / dVz + y - Vy1 ) >> 2;
  Px1 = ( ((Tx - x ) * (z - Vz1) ) / dVz + x + (dVx >> 1)) >> 2;
  Py1 = ( ((Ty - y ) * (z - Vz1) ) / dVz + y + (dVy >> 1)) >> 2;

  x = line3D.x2;
  y = line3D.y2;
  z = line3D.z2;

  Tx = (x * dTx)/dVx + Tx1;
  Ty = (y * dTy)/dVy + Ty1;

//  Px2 = ( ((Tx - x ) * (z - Vz1) ) / dVz + x - Vx1 ) >> 2;
//  Py2 = ( ((Ty - y ) * (z - Vz1) ) / dVz + y - Vy1 ) >> 2;
  Px2 = ( ((Tx - x ) * (z - Vz1) ) / dVz + x + (dVx >> 1)) >> 2;
  Py2 = ( ((Ty - y ) * (z - Vz1) ) / dVz + y + (dVy >> 1)) >> 2;

  if ( (lin->sx1 - Px1) || // Redraw only if the line has moved...
       (lin->sy1 - Py1) ||
       (lin->sx2 - Px2) ||          // This test pays off!!
       (lin->sy2 - Py2) ){

    grf -> set_color((U32)BLACK);
    ((class grafport *)grf) -> portline(lin->sx1, lin->sy1,	// erase old line
	                        lin->sx2, lin->sy2 );

    grf -> set_color((U32)WHITE);
    ((class grafport *)grf) -> portline(lin->sx1 = Px1, //Draw new line and save it
    	                        lin->sy1 = Py1,
				lin->sx2 = Px2,
				lin->sy2 = Py2);
  }
}
