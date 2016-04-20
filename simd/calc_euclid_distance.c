#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 128
#define LOOP 10000000

/*
http://d.hatena.ne.jp/ytakano/20100701/1277999108
*/

//extern float dist_normal(const float *v1, const float *v2, int len);


float
dist_normal(const float *v1, const float *v2, int len)
{
  float dist = 0.0;
  int   i;

  for (i = 0; i < len; i++) {
	float d;

	d  = v1[i] - v2[i];
	d *= d;

	dist += d;
  }
  return dist;
}

typedef float v4sf __attribute__ ((vector_size (16)));

typedef union {
  v4sf v;
  float f[4];
} f4vec;


float
dist_sse(float *v1, float *v2, int len)
{
  float dist = 0.0;
  int   i;

  for (i = 0; i < len; i += 4) {
	f4vec  d;
	f4vec *f4v1, *f4v2;

	f4v1 = (f4vec*)&v1[i];
	f4v2 = (f4vec*)&v2[i];

	d.v  = f4v1->v - f4v2->v;
	d.v *= d.v;

	dist += d.f[0] + d.f[1] + d.f[2] + d.f[3];
  }
  return dist;
}

double bench(){
  struct timeval t1, t2;
  float  v1[DIM];
  float  v2[DIM];
  int    i, j;
  double diff1, diff2;

  srand48(time(NULL));

  gettimeofday(&t1, NULL);
        
  for (i = 0; i < LOOP; i++) {
	for (j = 0; j < DIM; j++) {
	  v1[j] = (float)drand48();
	  v2[j] = (float)drand48();
	}
	dist_normal(v1, v2, DIM);
  }

  gettimeofday(&t2, NULL);

  diff1  = (t2.tv_sec + t2.tv_usec / 1000000.0);
  diff1 -= (t1.tv_sec + t1.tv_usec / 1000000.0);
  printf("elapsed time = %f\n", diff1);

  gettimeofday(&t1, NULL);
        
  for (i = 0; i < LOOP; i++) {
	for (j = 0; j < DIM; j++) {
	  v1[j] = (float)drand48();
	  v2[j] = (float)drand48();
	}
	dist_sse(v1, v2, DIM) ;
  }

  gettimeofday(&t2, NULL);

  diff2  = (t2.tv_sec + t2.tv_usec / 1000000.0);
  diff2 -= (t1.tv_sec + t1.tv_usec / 1000000.0);
  printf("elapsed time = %f\n", diff2);
  return (diff1 - diff2);
}


int
main(int argc, char *argv)
{
  bench();
  return 0;
}
