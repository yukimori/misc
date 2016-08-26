#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 128
#define LOOP 10000

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

/* void vectorize(float *v1, float *v2, f4vec* vec, int start, int idx) { */
/*     f4vec *f4v1, *f4v2; */
/*     int j = start + idx * 4; */

/*     f4v1 = (f4vec*)&v1[j]; */
/*     f4v2 = (f4vec*)&v2[j]; */

/*     vec->v = f4v1->v - f4v2->v; */
/*     vec->v = vec->v; */
/* } */

/* /\** */
/*   sseにある8個のレジスタをフル活用するバージョン */
/*  **\/ */
/* float dist_sse2(float *v1, float *v2, int len) { */
/*     float dist = 0.0; */
/*     f4vec d_sum, d[8]; */
/*     int i, j; */

/*     for (i = 0; i < len; i += 32) { */
/*         for (j=0; j < 7; j++) { */
/*             vectorize(v1, v2, &d[j], i, j); */
/*             d_sum.v += d[j].v; */
/*             dist += d_sum.f[0] + d_sum.f[1] + d_sum.f[2] + d_sum.f[3]; */
/*         } */
/*     } */

/*     return dist; */
/* } */


float
dist_sse(float *v1, float *v2, int len) {
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

double bench() {
  struct timeval t1, t2;
  float  v1[LOOP][DIM];
  float  v2[LOOP][DIM];
  float dist;
  int    i, j;
  double diff1, diff2;

  srand48(time(NULL));

  // prepare dataset
  for (i = 0; i < LOOP; i++) {
      for (j = 0; j < DIM; j++) {
          v1[i][j] = (float)drand48();
          v2[i][j] = (float)drand48();
      }
  }

  gettimeofday(&t1, NULL);
  for (i = 0; i < LOOP; i++) {
      dist = dist_normal(v1[i], v2[i], DIM);
  }
  gettimeofday(&t2, NULL);

  diff1  = (t2.tv_sec + t2.tv_usec / 1000000.0);
  diff1 -= (t1.tv_sec + t1.tv_usec / 1000000.0);
  printf("normal (last dist=%f)\n" , dist);
  printf("elapsed time = %f\n", diff1);

  gettimeofday(&t1, NULL);
  for (i = 0; i < LOOP; i++) {
	dist = dist_sse(v1[i], v2[i], DIM) ;
  }
  gettimeofday(&t2, NULL);
  diff2  = (t2.tv_sec + t2.tv_usec / 1000000.0);
  diff2 -= (t1.tv_sec + t1.tv_usec / 1000000.0);
  printf("sse (last dist=%f)\n" , dist);
  printf("elapsed time = %f\n", diff2);

  /* gettimeofday(&t1, NULL); */
  /* for (i = 0; i < LOOP; i++) { */
  /*   dist = dist_sse2(v1[i], v2[i], DIM) ; */
  /* } */
  /* gettimeofday(&t2, NULL); */
  /* diff2  = (t2.tv_sec + t2.tv_usec / 1000000.0); */
  /* diff2 -= (t1.tv_sec + t1.tv_usec / 1000000.0); */
  /* printf("sse2 (last dist=%f)\n" , dist); */
  /* printf("elapsed time = %f\n", diff2); */

  return (diff1 - diff2);

}


int
main(int argc, char *argv) {
  bench();
  return 0;
}
