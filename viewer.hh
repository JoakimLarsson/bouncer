/* viewer.h */

#ifndef viewer_h
#define viewer_h 1

#include "public.h"

#include "mover.hh"
#include "graphics.hh"

class viewer:public mover {
private:
  S32	Tx1, Ty1, Tx2, Ty2;		// view angle rectangle
  S32	Sx1, Sy1, Sx2, Sy2;		// Screen view rectangle
  S32	dVx, dVy, dVz, dTx, dTy;	// some commonly used constants
//  S8	reduct;				// reduction factor 1,2,4,8 etc
  S32	Vx1, Vy1, Vz1, Vx2, Vy2, Vz2;	// volume definition in real coords


  void calc_const();			// Help funktions
  void clip_max(line3Dtype *lin, S32 maxZ);
  void clip_min(line3Dtype *lin, S32 minZ);
  int  clipZ(line3Dtype *lin);
public:
  class pixels *grf;

       viewer(class pixels *g);

  void inc_zoom(){ };
  void dec_zoom(){ };

  void inc_X(S32 inc){ px+=inc; };
  void dec_X(S32 dec){ px-=dec; };
  void inc_Y(S32 inc){ py+=inc; };
  void dec_Y(S32 dec){ py-=dec; };
  void inc_Z(S32 inc){ pz+=inc; };
  void dec_Z(S32 dec){ pz-=dec; };

  void vline(linetype *lin);
};

#endif
