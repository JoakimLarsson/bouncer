/* cross.h */
#ifndef cross_h
#define cross_h 1

#include <math.h>

#include "public.h"

#include "mover.hh"

#define RAD (2<<4)

class cross:public mover {
  line3Dtype 	curlines[3];
  U32		curang;
  linetype 	lin[3];

public:

        cross(class viewer *v);
  void  init_trig();
  void	draw();
  void	erase();
};

#endif
