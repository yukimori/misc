#include <iostream>
#include <emmintrin.h>
#include <ctime>
#include <cmath>

/**
   http://felix.abecassis.me/2011/09/cpp-getting-started-with-sse/
 **/

class Timer
{
public:
  Timer(const std::string& name)
    : name_(name),
      start_(std::clock())
  {
  }
  ~Timer()
  {
	double elapsed = (double(std::clock() - start_) / double(CLOCKS_PER_SEC));
	std::cout << name_ << ": " << int(elapsed * 1000) << "ms" << std::endl;
  }
private:
  std::string name_;
  std::clock_t start_;
};                                                                                                                

#define TIMER(name) Timer timer__(name);

void normal(float* a, int N) {
  for (int i=0; i<N; ++i) {
	a[i] = std::sqrt(a[i]);
  }
}

void sse(float* a, int N) {
  //assume N%4==0
  int nb_iters = N/4;
  __m128* ptr = (__m128*)a;
  for(int i=0; i<nb_iters; ++i, ++ptr, a+=4) {
	_mm_store_ps(a, _mm_sqrt_ps(*ptr));
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
	return 1;
  }
  int N = atoi(argv[1]);

  float* a;
  posix_memalign((void**)&a, 16, N*sizeof(float));

  for (int i=0; i<N; ++i) {
	a[i] = 3141592.65358;
  }

  {
	TIMER("normal");
	normal(a, N);
  }

  for(int i=0; i<N; ++i) {
	a[i] = 3141592.65358;
  }

  {
	TIMER("sse");
	sse(a,N);
  }
}
