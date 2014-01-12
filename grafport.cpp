#include "pixels.hh"
#include "grafport.hh"

grafport::grafport()
{
  xfac = yfac = xdiv = ydiv = 1;
  xofs = yofs = 0;
}

/*
 * pline scales and positions a line
 */

void grafport::pline(U32 x1, U32 y1, U32 x2, U32 y2)
{
  gline( (int) (x1 * xfac) / xdiv + xofs,
	 (int) (y1 * yfac) / ydiv + yofs,
	 (int) (x2 * xfac) / xdiv + xofs,
	 (int) (y2 * yfac) / ydiv + yofs );
}
