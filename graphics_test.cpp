#include "public.h"

#include "grafport.hh"
#include "pixels.hh"

int main(){

  class graphics g;

  /* Line */
  g.set_color(WHITE);
  for (int y = 0; y < 500; y = y + 5)
    g.gline(0, y, g.get_kols() - 1, g.get_rows() - 1 - y);
};
