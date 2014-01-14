#include "public.h"

#include "pixels.hh"

main(){

  class pixels pixmap();

  printf("Pixmap %d,%d,%d\n", pixmap.get_rows(), pixmap.get_rows(), pixmap.get_rows(), get_depth());

  gport = new grafport();
  gport->set_div(3);
  vol = new viewer( gport );
};
