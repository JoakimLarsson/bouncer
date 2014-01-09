#ifndef volume_h
#define volume_h

#include "public.h"
// #include "graphics.h"

class volume {
private:
  S32	Tx1, Ty1, Tx2, Ty2;		// view angle rectangle
  S32	Sx1, Sy1, Sx2, Sy2;		// Screen view rectangle
  S32	dVx, dVy, dVz, dTx, dTy;	// some commonly used constants
  S8	reduct;				// reduction factor 1,2,4,8 etc

  void calc_const();			// Help funktion
public:
  S32	Vx1, Vy1, Vz1, Vx2, Vy2, Vz2;	// volume definition in real coords

       volume();
  void draw(int erase);
  void inc_zoom();
  void dec_zoom();
  void inc_X(S32 inc) { Vx1 += inc;  Vx2 += inc;  calc_const(); };
  void dec_X(S32 dec) { Vx1 -= dec;  Vx2 -= dec;  calc_const(); };
  void inc_Y(S32 inc) { Vy1 += inc;  Vy2 += inc;  calc_const(); };
  void dec_Y(S32 dec) { Vy1 -= dec;  Vy2 -= dec;  calc_const(); };
  void inc_Z(S32 inc) { Vz1 += inc;  Vz2 += inc;  calc_const(); };
  void dec_Z(S32 dec) { Vz1 -= dec;  Vz2 -= dec;  calc_const(); };

  void pline(S32 x1, S32 y1, S32 z1, 
	     S32 x2, S32 y2, S32 z2);
};

#endif