/* bouncer.h */

#ifndef bouncer_h
#define bouncer_h 1

#include "public.h"

#include "mover.hh"

class bouncer:public mover {
private:
  line3Dtype lines[12];
  S32  min_x, max_x, 	// bouncing limits
       min_y, max_y, 
       min_z, max_z;
  linetype lin[12];
  
  void setup_lines();	// help function
public:
       bouncer();
  void draw();
  void erase();

  void bounce_limits(S32 x1, S32 y1, S32 z1, S32 x2, S32 y2, S32 z2);
  void bounce_detect(class mover *t);
};

#endif
