#include <math.h>

#include "public.h"

#include "pixels.hh"
#include "grafport.hh"
#include "viewer.hh"
#include "mover.hh"
#include "bouncer.hh"

bouncer::bouncer()
{
  int i;

  for (i=0; i < 12; i++){		// define dummy line for first
    lin[i].sx1 =		// erase of 2D line
    lin[i].sy1 =
    lin[i].sx2 =
    lin[i].sy2 = (S16) 0;
//    lin[i].line3D = lines[i];
  }
}

void bouncer::draw()
{
  int i;

  for (i=0; i < 12; i++){
    lin[i].line3D = lines[i];
    mline(&lin[i]);
  }
}


void bouncer::erase()
{
  int i;

  (view->grf) -> set_color((U32)BLACK);
  for (i = 0; i < 12; i++){
    ((class grafport *)(view->grf)) -> pline( lin[i].sx1, lin[i].sy1,	// erase old lines
                          lin[i].sx2, lin[i].sy2 );

    lin[i].sx1 = lin[i].sy1 = lin[i].sx2 = lin[i].sy2 = (S16) 0;
  }
}

void bouncer::setup_lines()
{
  lines[0].x1 = min_x; lines[0].y1 = min_y; lines[0].z1 = min_z; 
  lines[0].x2 = max_x; lines[0].y2 = min_y; lines[0].z2 = min_z; 

// Copy previous line  Reset last line	    Set new line
  lines[1] = lines[0]; lines[1].x2 = min_x; lines[1].y2 = max_y;
  lines[2] = lines[1]; lines[2].y2 = min_y; lines[2].z2 = max_z;
// New basepoint
  lines[3] = lines[2]; lines[3].z1 = max_z; lines[3].y2 = max_y;
  lines[4] = lines[3]; lines[4].y2 = min_y; lines[4].x2 = max_x;
// New basepoint
  lines[5] = lines[4]; lines[5].x1 = max_x; lines[5].z2 = min_z;
  lines[6] = lines[5]; lines[6].z2 = max_z; lines[6].y2 = max_y;
// New basepoint
  lines[7] = lines[6]; lines[7].y1 = max_y; lines[7].x1 = min_x;
// New basepoint
  lines[8] = lines[7]; lines[8].x2 = min_x; lines[8].z1 = min_z;
// New basepoint
  lines[9]  = lines[8]; lines[9].z2 = min_z; lines[9].x1 = max_x;
// New basepoint
  lines[10] = lines[9]; lines[10].x2 = max_x; lines[10].y1 = min_y;
  lines[11] = lines[10];lines[11].y1 = max_y; lines[11].z1 = max_z;
}


void bouncer::bounce_limits(S32 x1, S32 y1, S32 z1, S32 x2, S32 y2, S32 z2)
{
  min_x = x1 << 4; max_x = x2 << 4;
  min_y = y1 << 4; max_y = y2 << 4;
  min_z = z1 << 4; max_z = z2 << 4;
  setup_lines();
}

void bouncer::bounce_detect(class mover *t)
{
    if (t->px > max_x){		// Correct X values
      t->px  = max_x - (t->px - max_x);
      t->dsx = -t->dsx;
    }else if (t->px < min_x){
      t->px  = min_x + (min_x - t->px);
      t->dsx = -t->dsx;
    }
    if (t->py > max_y){		// Correct Y values
      t->py  = max_y - (t->py - max_y);
      t->dsy = -t->dsy;
    }else if (t->py < min_y){
      t->py  = min_y + (min_y - t->py);
      t->dsy = -t->dsy;
    }
    if (t->pz > max_z){		// Correct Z values
      t->pz  = max_z - (t->pz - max_z);
      t->dsz = -t->dsz;
    }else if (t->pz < min_z){
      t->pz  = min_z + (min_z - t->pz);
      t->dsz = -t->dsz;
    }
}
