#include <emmintrin.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <chrono>

/*
http://daily.belltail.jp/?p=1520
osakana/stopwatchは非公開ライブライリなので置き換える必要がある

20160414 動作環境がavx非対応なのでnormalとsseのみ
sseの方が時間がかかる
20160610 変数のメモリのアラインメントを修正することでsseが早くなることを確認
http://kawa0810.hateblo.jp/entry/20120430/1335775256

g++ -std=c++11 -Wall calc_innerproduct.cpp -O3 -msse4.2 -o calc_innerproduct

feature:
計算を以下のように拡大する
L1距離の計算
L2距離の計算
ハミング距離の計算
http://d.hatena.ne.jp/wosugi/20131208%231386514756
 */

float dot_normal(const float *vec1, const float *vec2, unsigned n) {
    float sum = 0;
    for (unsigned i = 0; i < n; ++i) {
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

void print_result(int len, std::string type, double elapsed, float sum=0.0) {
  std::cout << std::setw(12) << std::right << len << ",";
  std::cout << std::setw(6) << std::right << type << ",";
  std::cout << std::setw(12) << std::right << elapsed << ",";
  std::cout << std::setw(10) << std::right << sum << std::endl;
}

template< typename F, class Period = std::ratio<1> >
std::chrono::duration<double, Period> stopwatch(F&& func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  return std::chrono::duration_cast<std::chrono::duration<double, Period> >(std::chrono::high_resolution_clock::now() - start);
}

// template<class T>
// double calc_for_a_moment(T t, unsined ms) {
  
// }

int main() {
    const unsigned len_begin = 8;
    const unsigned len_end   = 512 * 1024;
    const unsigned len_fact  = 2;
    
    std::mt19937 rng;
    std::uniform_real_distribution<> dst(-1, 1);

    typedef std::chrono::duration<double, std::ratio<1, 1000> > Milli;

    std::cout << "size,{sse,normal},elapsedtime[ms],sum" << std::endl;

    for (unsigned len = len_begin; len <= len_end; len *= len_fact) {
        // SSEで効率的にレジスタに読み込むためメモリを16byte境界にアライメントする
        float* p1;
        // 動的にheapに整列したメモリを確保。malloc,newは整列したメモリを確保できない
        // 引数は 1.メモリの先頭 2.揃えたいメモリアライメント 3.確保したいメモリサイズ
        posix_memalign(reinterpret_cast<void**>(&p1), 16, (len)*sizeof(float));
        float* p2;
        posix_memalign(reinterpret_cast<void**>(&p2), 16, (len)*sizeof(float));
        float *vec1 = p1;
        float *vec2 = p2;

        std::generate(vec1, vec1+len, [&rng, &dst](){return dst(rng);});
        std::generate(vec2, vec2+len, [&rng, &dst](){return dst(rng);});
  
        Milli sse_time = stopwatch([vec1, vec2, len](){
                return dot_sse(vec1, vec2, len);
            });
        print_result(len, "sse", sse_time.count());

        float sum = 0.0;
        int N = 100;
        auto time_point = std::chrono::high_resolution_clock::now();
        for (int i=0; i < N ; ++i) {
            sum = dot_sse(vec1, vec2, len);
        }
        auto duration = std::chrono::high_resolution_clock::now() - time_point;
        auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration);
        print_result(len, "sse", (micros.count()/N), sum);

        time_point = std::chrono::high_resolution_clock::now();
        for (int i=0; i<N; ++i) {
            sum = dot_normal(vec1, vec2, len);
        }
        duration = std::chrono::high_resolution_clock::now() - time_point;
        micros = std::chrono::duration_cast<std::chrono::microseconds>(duration);
        print_result(len, "normal", (micros.count()/N), sum);

        free(p1);
        free(p2);
    }
}
