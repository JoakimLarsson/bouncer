#include "public.h"

#include "bouncer.hh"
#include "viewer.hh"
#include "grafport.hh"

int main(){
  class bouncer  bon;
  class bouncer  bon2;
  class grafport g;
  class viewer   vol(&g);

  /* set it up */
  bon.view = &vol;
  bon.bounce_limits(0, 0, 0, 100, 100, 100);
  bon.set_position(1015, 1015, 1050);
  bon.draw();

  bon2.view = &vol;
  bon2.bounce_limits(0, 0, 0, 25, 200, 100);
  bon2.set_position(875, 965, 1050);
  bon2.draw();
};
