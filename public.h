/* public.h */
#ifndef public_h
#define public_h 1

#define BORLAND 0	/* 0 if we are NOT using Borland C++ */
#define DEBUG 0
#define MAXOBJ 23

#if BORLAND<1
#define far
#endif


#define debugio stdout

#define S8	signed char

#define	U8	unsigned char

#define U16	unsigned short
#define MAX_U16	0xffff

#define S16	signed short
#define MAX_S16	0x7fff

#define U32	unsigned long
#define MAX_U32	0xffffffff

#define S32	signed long
#define MAX_S32	0x7fffffff

#define	TRUE	-1
#define FALSE	0

// macros for use of precompiled trig values
extern double coses[];
extern double sines[];

#define COSES 360
#define SINES 360
//#define sin(x) sines[SINES*(int)((x)%360)/360]
//#define cos(x) coses[COSES*(int)((x)%360)/360]

typedef struct {
  S32 x1, y1, z1;
  S32 x2, y2, z2;
} line3Dtype;

typedef struct  {
  line3Dtype line3D;
  U16 sx1, sy1, sx2, sy2;
} linetype;

#endif
