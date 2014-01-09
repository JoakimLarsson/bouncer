#ifndef grafport_h
#define grafport_h 1

#include "public.h"

#include "graphics.hh"

class grafport:public graphics {
private:
  S16 xfac, yfac;
  S16 xdiv, ydiv;
  S16 xofs, yofs;
public:
       grafport();
  void set_xfac(S32 i){xfac = i;};
  void set_yfac(S32 i){yfac = i;};
  void set_fac(S32 i){xfac = i; yfac = i;};
  void set_xdiv(S32 i){xdiv = i;};
  void set_ydiv(S32 i){ydiv = i;};
  void set_div(S32 i){xdiv = i; ydiv = i;};
  void set_xofs(S32 i){xofs = i;};
  void set_yofs(S32 i){yofs = i;};
  void set_ofs(S32 i){xofs = i; yofs = i;};
  void portline(U32 x1, U32 y1, U32 x2, U32 y2);
};

#endif
