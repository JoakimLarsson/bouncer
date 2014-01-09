/* mover.h */

#ifndef mover_h
#define mover_h 1

#include "public.h"

class mover {
  void	setup_increments();	// help function
public:
  S32	px, py, pz;	// Position in true coordinates
  S32	dsx, dsy, dsz;	// Direktion and speed in relative units
  S32	speed;		// explicit speed
  S32	dx, dy, dz;	// direction vector (length is of no interest)
  U32	radie;		// radie from mover koordinate to outermost point
  class bouncer *boun;	// optional bouncer object reference
  class viewer  *view;	// reference to 3D viewer object
  
  			mover();
  		S32	get_px();
  		S32	get_py();
  		S32	get_pz();
  		void	move();
		void 	set_position(U32 x, U32 y, U32 z);
  		void	set_direction(S32 rx, S32 ry, S32 rz);
		void 	set_speed(S32);
		void	set_bouncer(class bouncer *b){ boun = b; };
                void	mline(linetype *lin);
  virtual	void	draw(){};
  virtual	void	erase(){};
};
#endif

#if mover_h
/* is STILL defined */
#else
/* is NOT defined */
#endif
