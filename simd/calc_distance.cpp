#include <nmmintrin.h>
#include <cstdio>
#include <cassert>
#include <ctime>
#include <string>
#include <iostream>


/**
   ref:
   https://github.com/wosugi/benchmark-distance/blob/master/benchmark-distance/main.cpp
   http://www.slideshare.net/FukushimaNorishige/simd-10548373?from_action=save
   http://www.slideshare.net/FukushimaNorishige/simd-10548373
   
**/

// Parameter D (dimension of a vector with uchar elements)
// has to be set in multiples of ALIGN (i.e., 16).
// This benchmark treats the length of a binary vector as 8D.

const int ALIGN=16; // alignment step for SSE
const unsigned D=128; // dimension of a vector with uchar elements
const unsigned N=1024*1024*4; // # of dictionary vectors

inline std::string to_binary(unsigned char b) {
    std::string str("........");
    for (unsigned i=0; i < 8; ++i) {
        if (b & (1<<i)) {
            str[8-1-i]='#';
        }
    }
    return str;
}

void print128_num(__m128i var) {
    uint16_t *val = reinterpret_cast<uint16_t*>(&var);
    for (int i=0; i < 8; ++i) {
        std::cout << val[0] << std::endl;
    }
}

inline int dist_l2_sse(const unsigned char* p, const unsigned char* q) {
    // __m128i 整数
    __m128i t = _mm_setzero_si128();
    
    for (unsigned d=0; d < D; d += ALIGN) {
        __m128i pm = _mm_load_si128((__m128i*)(p+d));
        __m128i qm = _mm_load_si128((__m128i*)(q+d));
        __m128i sublo = _mm_sub_epi16(
            _mm_unpacklo_epi8(pm,_mm_setzero_si128()),
            _mm_unpacklo_epi8(qm,_mm_setzero_si128())
                                    );
        t=_mm_add_epi32(t,
                        _mm_madd_epi16(sublo,sublo)
                        );
        __m128i subhi=_mm_sub_epi16(
            _mm_unpackhi_epi8(pm,_mm_setzero_si128()),
            _mm_unpackhi_epi8(qm,_mm_setzero_si128())
                                    );
        t = _mm_add_epi32(t, _mm_madd_epi16(subhi,subhi));
    }

    // __m128i.m128i_i32フィールドはgccでは実装されていない
    // http://stackoverflow.com/questions/13257166/print-a-m128i-variable
    //    return int(t.m128i_i32[0]+t.m128i_i32[1]+t.m128i_i32[2]+t.m128i_i32[3]);
    //    print128_num(t);
    int dist[4] __attribute__((aligned(16)));
    _mm_store_si128(reinterpret_cast<__m128i*>(&dist), t);
    return dist[0]+dist[1]+dist[2]+dist[3];
}

int main() {
    std::string bit = to_binary('c');
    std::cout << bit << std::endl;


    printf("Dimension of a vector (D): %d\n",D);
    printf("# of dictionary vectors (N): %d\n",N);
    printf("-----------------------------------------\n");


    unsigned char* dict=reinterpret_cast<unsigned char*>(_mm_malloc(N*D,ALIGN));
    unsigned char* query=reinterpret_cast<unsigned char*>(_mm_malloc(D,ALIGN));

    // unsigned char a = '0';
    // unsigned char b = 'c';
    // int dist = dist_l2_sse(&a, &b);
    // std::cout << dist << std::endl;
}
