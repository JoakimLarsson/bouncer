#include "public.h"

#include "grafport.hh"
#include "pixels.hh"

int main(){

  class grafport g;

  g.set_color(GREEN);
  g.set_div(3); // Set up a scal factor

  // Draw a line using the graphics class
  g.gline(100, 100, 300, 200);
  g.gline(110, 100, 310, 200);

  // Draw the same line using the grafport class
  g.pline(100, 100, 300, 200);
  g.pline(110, 100, 310, 200);

  /* It should look the same but three times smaller and closer to origo (left upper pixel) */

};
