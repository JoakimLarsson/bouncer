#include <unistd.h>
#include "public.h"

#include "cross.hh"
#include "bouncer.hh"
#include "viewer.hh"
#include "grafport.hh"

#define CROSSES 3

int main(){
  class mover    *obj[CROSSES];
  class bouncer  bon;
  class bouncer  bon2;
  class grafport g;
  class viewer   vol(&g);

  /* set it up */
  bon.view = &vol;
  bon.bounce_limits(0, 0, 0, 150, 153, 200);
  bon.set_position(915, 915, 950);
  bon.draw();

  for (int i = 0; i < CROSSES; i++){
    obj[i] = new cross(&vol);
    obj[i] -> set_bouncer(&bon);
    obj[i] -> set_position(i % 10 + 5, i % 50 + 45, i % 50 + 45);
    obj[i] -> set_speed(i % 7 + 1);
#if 0
    obj[i] -> set_direction((float)i / CROSSES * 640 + 1,
    			    (float)i / (CROSSES * 2) * 480 + 1, 350);
#else
    obj[i] -> set_direction((i + 1) * CROSSES % 150,(i + 1) * CROSSES % 153,(i + 1) * CROSSES % 200);
#endif
    //    ((class cross *)obj[i]) -> color = RED;
  }

  while(1){
    for (int i = 0; i < CROSSES; i++){
      usleep(1500 / CROSSES);
      obj[i]->move();
      (obj[i]->boun)->bounce_detect(obj[i]);
      obj[i]->draw();
    }
    bon.draw();
  }
};
