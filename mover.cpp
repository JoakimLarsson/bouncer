#include <stdio.h>
#include <math.h>

#include "public.h"

#if BORLAND
#include <conio.h>
#endif

#include "mover.hh"
#include "viewer.hh"
#include "bouncer.hh"

mover::mover() // class constructor
{
  px = py = pz = dx = dy = dz = dsx = dsy = dsz = speed = 0;
  boun = (class bouncer *) 0L;
};

inline S32 mover::get_px(){ return (boun != (class bouncer *) 0L) ? 
			    px + boun -> get_px() : px; }
inline S32 mover::get_py(){ return (boun != (class bouncer *) 0L) ? 
			    py + boun -> get_py() : py; }
inline S32 mover::get_pz(){ return (boun != (class bouncer *) 0L) ?
			    pz + boun -> get_pz() : pz; }

void mover::mline(linetype *lin)
{
  // Add local world coordinates
  lin->line3D.x1 += get_px(); // px + boun -> px;
  lin->line3D.y1 += get_py(); // py + boun -> py;
  lin->line3D.z1 += get_pz(); // pz + boun -> pz;
  lin->line3D.x2 += get_px(); // px + boun -> px;
  lin->line3D.y2 += get_py(); // py + boun -> py;
  lin->line3D.z2 += get_pz(); // pz + boun -> pz;

  view -> vline(lin);
}

void mover::set_position(U32 x, U32 y, U32 z)
{
  px = x > (MAX_U32 >> 4) ? MAX_U32 - 0xf : x << 4;
  py = y > (MAX_U32 >> 4) ? MAX_U32 - 0xf : y << 4;
  pz = z > (MAX_U32 >> 4) ? MAX_U32 - 0xf : z << 4;
};

void mover::move()
{
  px += dsx;
  py += dsy;
  pz += dsz;
}


void mover::setup_increments()
{
  double kvot = speed / (double) sqrt(dx * dx + dy * dy + dz * dz);
   dsx = (int) ((dx << 4) * kvot);
   dsy = (int) ((dy << 4) * kvot);
   dsz = (int) ((dz << 4) * kvot);
}

void mover::set_direction(S32 x, S32 y, S32 z)
{
  dx = x; dy = y; dz = z;
  if (speed)
    setup_increments();
}

void mover::set_speed(S32 s)
{
  speed = s;
  if (dx + dy + dz)
    setup_increments();
}
