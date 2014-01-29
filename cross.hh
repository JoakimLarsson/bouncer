/* cross.h */
#ifndef cross_h
#define cross_h 1

#include <math.h>

#include "public.h"
#include "bouncer.hh"
#include "mover.hh"

#define RAD (2<<4)

class cross:public bouncer {
  line3Dtype 	curlines[3];
  linetype 	lin[3];

public:
  U32           color;
  cross(class viewer *v);
  void  init_trig();
  void	draw();
  void	erase();
};

#endif
