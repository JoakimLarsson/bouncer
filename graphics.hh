#ifndef graphics_h
#define graphics_h 1

#include "public.h"

#include "pixels.hh"

class graphics: public pixels {
public:
  void gline(U32 x1, U32 y1, U32 x2, U32 y2);
};

#endif
