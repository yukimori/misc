#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <nmmintrin.h>

/**
   ref:
   http://d.hatena.ne.jp/sleepy_yoshi/20121211/p1

   g++ -O2 -Wall -msse4.2 -std=c++0x test_popcount.cpp
 **/
size_t
popcount (std::vector<uint64_t> &x_vec)
{
    size_t c = 0;
    for (int i = 0; i < (int)x_vec.size(); i++) {
        c += _mm_popcnt_u64( x_vec[ i ] );
    }
    return c;
}

int
main (int argc, char *argv[])
{
    std::vector<uint64_t> x_vec;

    x_vec.push_back( (uint64_t) 1 );
    x_vec.push_back( (uint64_t) 1 );

    std::cout << popcount( x_vec ) << std::endl;

    return 0;
}
