
/*
 * Test application for the pixels class
*/

#include <stdio.h>

#include "public.h"
#include "pixels.hh"

int main()
{
  class pixels p;
  int col2;
  unsigned int white, black, red, green, blue;

  if (p.get_depth() == 16){
    white = WHITE16;
    black = BLACK16;
    red = RED16;
    blue = BLUE16;
    green = GREEN16;
  }
  else if (p.get_depth() == 32){
    white = WHITE32;
    black = BLACK32;
    red = RED32;
    blue = BLUE32;
    green = GREEN32;
  }


  /* Fill some squares, check pixel aspect ratio */
  printf("Color fill, put %08x\n", white);
  p.set_color(white);
  for (int x = 0; x < (int) p.get_kols(); x++)
    for (int y = 0; y < (int) p.get_rows(); y++)
      p.set_pixel(x, y);

  col2 = p.get_pixel(500,500);
  printf("Color readback, got %08x\n", col2);

  p.set_color(blue);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++)
      p.set_pixel(50 + x,50 + y);
  p.set_color(green);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++)
      p.set_pixel(150 + x,50 + y);
  p.set_color(red);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++)
      p.set_pixel(150 + x,150 + y);
  p.set_color(black);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++)
      p.set_pixel(50 + x,150 + y);
  /* TODO: Auto check */
  /* There should be             Blue    Green 
     Four colored squares        Black   Red 
     on screen  
  */

  /* Readback pixel */
  {
    unsigned int col, col2;

    col = 0x88442211 & ((1 << p.get_depth()) - 1); // Mask to the right bit depth
    p.set_color(col);
    p.set_pixel(500,500);
    col2 = p.get_pixel(500,500);
    if (col != col2)
      printf("Wrong color readback, expected %08x but got %08x\n", col, col2);
  }
  /* XOR pixel */
  {
    unsigned int col, col2, col3;

    col  = 0x88442211 & ((1 << p.get_depth()) - 1); // Mask to the right bit depth
    col2 = 0x11224488 & ((1 << p.get_depth()) - 1); // Mask to the right bit depth
    p.set_color(col);
    p.set_pixel(600,500);
    p.set_color(col2);
    p.xor_pixel(600, 500);
    col3 = p.get_pixel(600,500);
    if ((col ^ col2) != col3)
      printf("Wrong color readback, expected %08x but got %08x\n", col ^ col2, col3);
  }

}
