#include <cstdio>
#include <xmmintrin.h>

/**
   http://i-saint.hatenablog.com/entry/20101003/1286043166
   gccは-msseオプションがコンパイル時に必要
 **/

int main() {
  //sseのデータ型 16byteにアラインメントされたデータ
  __m128 a, b, c;

  //各種intrinsicsを使って4要素を操作する
  //floatは4byte？
  a = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
  b = _mm_setr_ps(5.0f, 6.0f, 7.0f, 8.0f);
  c = _mm_add_ps(a, b);
  c = _mm_mul_ps(c, a);
  c = _mm_sub_ps(c, b);

  float* r = (float*)&c;
  printf("%.2f, %.2f, %.2f, %.2f\n", r[0], r[1], r[2], r[3]);
}
