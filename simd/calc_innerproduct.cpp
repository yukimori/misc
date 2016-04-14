#include <iostream>
#include <iomanip>

#include <random>
#include <algorithm>

#include <emmintrin.h>

#include <chrono>

/*
http://daily.belltail.jp/?p=1520
osakana/stopwatchは非公開ライブライリなので置き換える必要がある

20160414 動作環境がavx非対応なのでnormalとsseのみ
sseの方が時間がかかる
 */

float dot_normal(const float *vec1, const float *vec2, unsigned n)
{
  float sum = 0;
  for(unsigned i = 0; i < n; ++i) {
	sum += vec1[i] * vec2[i];
  }
  //  std::cout << sum << std::endl;
  return sum;
}

float dot_sse(const float *vec1, const float *vec2, unsigned n)
{
  __m128 u = {0};
  for (unsigned i = 0; i < n; i += 4)
	{
	  __m128 w = _mm_load_ps(&vec1[i]);
	  __m128 x = _mm_load_ps(&vec2[i]);

	  x = _mm_mul_ps(w, x);
	  u = _mm_add_ps(u, x);
	}
  __attribute__((aligned(16))) float t[4] = {0};
  _mm_store_ps(t, u);
  float sum = t[0] + t[1] + t[2] + t[3];
  //  std::cout << sum << std::endl;
  return sum;
}

void print_result(int len, std::string type, int elapsed, float sum) {
  std::cout << std::setw(12) << std::right << len << ",";
  std::cout << std::setw(6) << std::right << type << ",";
  std::cout << std::setw(12) << std::right << elapsed << ",";
  std::cout << std::setw(10) << std::right << sum << std::endl;
}

int main()
{
  const unsigned len_begin = 8;
  const unsigned len_end   = 512 * 1024 ;
  const unsigned len_fact  = 2;

  std::mt19937 rng;
  std::uniform_real_distribution<> dst(-1, 1);

  std::cout << "size,{sse,normal},elapsedtime[micro seconds],sum" << std::endl;

  for(unsigned len = len_begin; len <= len_end; len *= len_fact)
{
  float* p1;
  posix_memalign((void**)&p1, 16, (len+8)*sizeof(float));
  float* p2;
  posix_memalign((void**)&p2, 16, (len+8)*sizeof(float));
  float *vec1 = p1;
  float *vec2 = p2;

  std::generate(vec1, vec1+len, [&rng, &dst](){return dst(rng);});
  std::generate(vec2, vec2+len, [&rng, &dst](){return dst(rng);});
  

  auto time_point = std::chrono::high_resolution_clock::now();
  float sum = dot_sse(vec1, vec2, len);
  auto duration = std::chrono::high_resolution_clock::now() - time_point;
  auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration);
  print_result(len, "sse", micros.count(), sum);
  
  
  time_point = std::chrono::high_resolution_clock::now();
  sum = dot_normal(vec1, vec2, len);
  duration = std::chrono::high_resolution_clock::now() - time_point;
  micros = std::chrono::duration_cast<std::chrono::microseconds>(duration);
  print_result(len, "normal", micros.count(), sum);


  delete[] p1;
  delete[] p2;
 }
}
