#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "public.h"

#if BORLAND
#include <conio.h>
#endif

#include "viewer.hh"
#include "cross.hh"
#include "bouncer.hh"
#include "grafport.hh"

class mover    *obj[MAXOBJ];
class bouncer  bon, bon2, space;
class viewer   vol;
class grafport gport;

void inc_speed(int inc)
{
  int i;

  for (i = 0; i < MAXOBJ; i++)
      obj[i]->set_speed(obj[i]->speed * inc);
}

void dec_speed(int dec)
{
  int i;

  for (i = 0; i < MAXOBJ; i++)
      obj[i]->set_speed(obj[i]->speed / dec);
}

void erase_all()
{
  int i;

  for (i = 0; i < MAXOBJ; i++){
    obj[i]->erase();
  }
  bon->erase();
  bon2->erase();
}

void fwd(int j)
{
  int i;

  while(j--){
    for (i = 0; i < MAXOBJ; i++){
      obj[i]->move();
      (obj[i]->boun)->bounce_detect(obj[i]);
      obj[i]->draw();
    }
  }
}

void bwd(int j)
{
  int i;

  for (i = 0; i < MAXOBJ; i++){
    obj[i]->dsx *= -1;
    obj[i]->dsy *= -1;
    obj[i]->dsz *= -1;
  }
  while(j--){
//    printf("%d \r", j);
    for (i = 0; i < MAXOBJ; i++){
      obj[i]->move();
      (obj[i]->boun)->bounce_detect(obj[i]);
      obj[i]->draw();
    }
  }
  for (i = 0; i < MAXOBJ; i++){
    obj[i]->dsx *= -1;
    obj[i]->dsy *= -1;
    obj[i]->dsz *= -1;
  }
}

void go()
{
  int i;

#if BORLAND
  while(!kbhit())
#endif
  {
//    printf("%d %08ld %08ld %08ld %08ld\r", (*j)++,
//           vol->Vx1, vol->Vy1, vol->Vx2, vol->Vy2);
    for (i = 0; i < MAXOBJ; i++){
      obj[i]->move();
      (obj[i]->boun)->bounce_detect(obj[i]);
      obj[i]->draw();
    }
    bon->draw();
    bon2->draw();
  }
}

void time()
{
  int i,j;
  clock_t beg, end;

  j = 200;
  beg = clock();
  while(j--){
//    printf("%d %08ld %08ld %08ld %08ld\r", (*j)++,
//           vol->Vx1, vol->Vy1, vol->Vx2, vol->Vy2);
    for (i = 0; i < MAXOBJ; i++){
      obj[i]->move();
      (obj[i]->boun)->bounce_detect(obj[i]);
      obj[i]->draw();
    }
  }
  end = clock();
  printf("%lx - %lx -->> %lx \r", beg, end, end-beg);
}

main(){
  char cmd;
  int frame,j,i;
  int running;

#if 0 // BORLAND // If Borland C++

  int ErrorCode;
  int GraphMode; 		
  int GraphDriver = DETECT; 		/* Request auto-detection	*/


  initgraph( &GraphDriver, &GraphMode, "" );
  ErrorCode = graphresult();		/* Read result of initialization*/
  if( ErrorCode != grOk ){		/* Error occured during init	*/
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );

    exit( 1 );
  }

#endif

  //  gport = new grafport();
  gport->set_div(3);
  //  vol = new viewer( gport );
  //space = new bouncer();
//  space->bounce_limits(10, 10, 10, 100000, 100000, 100000);

  //bon = new bouncer();
  bon -> view = vol;
  bon-> bounce_limits(0, 0, 0, 100, 100, 100);
  bon -> set_position(1015, 1015, 1050);

  //bon2 = new bouncer();
  bon2 -> view = vol;
  bon2 -> bounce_limits(0, 0, 0, 25, 200, 100);
  bon2 -> set_position(1175, 965, 1050);


//  bon -> draw();
//  obj[0] = bon;

  for (i=0; i<MAXOBJ; i++){
    obj[i] = new cross(vol);
    if ( i & 1 )
      obj[i] -> set_bouncer(bon);
    else
      obj[i] -> set_bouncer(bon2);
    obj[i] -> set_position(10, 50, 50);
    obj[i] -> set_direction((float)i / MAXOBJ * 640 + 1,
    			    (float)i / (MAXOBJ * 2) * 480 + 1, 350);
    obj[i] -> set_speed(i % 7 + 5);
  }

  frame = 0;
  running = FALSE;

//  time();
//fx  exit(1);

  while(1){
#if BORLAND
    printf(" \r", frame);	 // just to be able to catch Control-C
    cmd = getch();
#endif
//    printf("%c - %02x \r", cmd, (int) cmd);
    switch ((int) (0xff & cmd) ){
      case 'f' : fwd(1); frame++; break;
      case 'F' : fwd(10); frame+=10; break;
      case 'a' : fwd(100); frame+=100; break;
//      case 'A' : fwd(1000); frame+=1000; break;
      case 'b' : bwd(1); frame--; break;
      case 'B' : bwd(10); frame-=10; break;
      case 'r' : bwd(100); frame-=100; break;
//      case 'R' : bwd(1000); frame-=1000; break;
      case 'i'    : inc_speed(2); break;
      case 'I'    : inc_speed(4); break;
      case 'd'    : dec_speed(2); break;
      case 'D'    : dec_speed(4); break;
      case 'g'    : running = TRUE; break;
      case 's'    : running = FALSE; break;
      case 'z'    : erase_all(); vol->inc_Z(10<<4); break;
      case 'Z'    : erase_all(); vol->dec_Z(10<<4); break;
      case 'K'    : erase_all(); vol->inc_X(10<<4); break;
      case 'M'    : erase_all(); vol->dec_X(10<<4); break;
      case 'H'    : erase_all(); vol->inc_Y(10<<4); break;
      case 'P'    : erase_all(); vol->dec_Y(10<<4); break;
      case 'q'	  : exit(0);
      case 0x8f   : erase_all(); vol->inc_Z(10<<4); break;
      case 0x91   : erase_all(); vol->dec_Z(10<<4); break;
      case 't'    : time(); 
#if BORLAND
	getch(); 
#endif
	break;
      default: break;
    }
    if (running == TRUE)
      go();
  }
};
