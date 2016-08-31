# files
test_sse_simple.cpp
 sseのテストコード．説明などを記述している

# build
-msse4.2が必要
g++ -std=c++11 -msse4.2 test_sse_simple.cpp
g++ -std=c++11 -Wall calc_innerproduct.cpp -O3 -msse4.2 -o calc_innerproduct

# Result:calc_innerproduct
- sumが微妙に異なる（計算誤差が発生している？）
- sseが2～3倍高速

size,{sse,normal},elapsedtime[ms],sum
           8,   sse,           0,  -0.57812
           8,normal,           0,  -0.57812
          16,   sse,           0, -0.500153
          16,normal,           0, -0.500153
          32,   sse,           0,   3.08292
          32,normal,           0,   3.08292
          64,   sse,           0,   2.90202
          64,normal,           0,   2.90202
         128,   sse,           0,  -3.75107
         128,normal,           0,  -3.75107
         256,   sse,           0,  -2.74286
         256,normal,           0,  -2.74286
         512,   sse,           0, -0.315992
         512,normal,           1, -0.315995
        1024,   sse,           0,  -10.2694
        1024,normal,           2,  -10.2695
        2048,   sse,           1,   13.0692
        2048,normal,           5,   13.0692
        4096,   sse,           3,   2.79282
        4096,normal,          10,   2.79281
        8192,   sse,           6,  -38.9192
        8192,normal,          20,  -38.9191
       16384,   sse,          12,   63.4561
       16384,normal,          14,   63.4562
       32768,   sse,           9,   -43.545
       32768,normal,          28,   -43.545
       65536,   sse,          19,  -53.4902
       65536,normal,          60,  -53.4907
      131072,   sse,          42,   168.915
      131072,normal,         118,   168.915
      262144,   sse,          83,  -114.572
      262144,normal,         231,  -114.571
      524288,   sse,         171,   312.416
      524288,normal,         473,   312.422

# Result:calc_euclid_distance
ほとんど変わらない（sseの処理がおかしい？）
normal elapsed time = 32.585665
sse    elapsed time = 28.480349