#include <cstdio>
#include <xmmintrin.h>
#include <iostream>

/**
   history:
    20160826 sseのテストコード
    sse4.2を利用してfloat,intを4個一度にロードストアできることを確認
    16バイトアラインを実施

   memo:
    コンパイル時に-msseオプションが必要
    g++ -msse4.2 test_sse_simple.cpp

   ref:
    http://i-saint.hatenablog.com/entry/20101003/1286043166
    http://nu-pan.hatenablog.com/entry/20140421/1398069361
    http://www.slideshare.net/FukushimaNorishige/simd-10548373
 **/

// 配列の先頭アドレスが16バイトアラインされる
// 16byte = 128bit
float hoge[4] __attribute__((aligned(16)));

//同じことをtypedefで
// typedef float float_4a[4] __attribute__((aligned(16)));
// float_4a hoge;

//構造体の先頭アドレスとsizeof(piyo)が16バイトアラインされる
//メンバのアラインメントについてはノータッチ
struct piyo{
    float foo;
    float bar;
}__attribute__((aligned(16)));

//hogeは16バイトアラインされる
//piyo hoge;

/*
  C++型  レジスタ型 ロード命令        ストア命令
  float  __m128     _mm_load_ps()     _mm_store_ps()
  double __m128d    _mm_load_pd()     _mm_store_pd()
  整数   __m128i    _mm_load_si128()  _mm_store_si128()
*/
void examin_loadstore() {
    // piyoの宣言時にalignedを使っているのでpは16バイトアラインされる
    piyo* p = new piyo;

    // 配列の先頭アドレスが16バイトアラインされる
    // sseは128ビット（=16バイト）レジスタをもつ
    float Hoge[4] __attribute__((aligned(16)));  // ロード元
    float Piyo[4] __attribute__((aligned(16)));  // ストア先
    __m128 Acc;  // レジスタ

    int IntHoge[4] __attribute__((aligned(16)));  // load
    int IntPiyo[4] __attribute__((aligned(16)));  // store
    __m128i IntAcc = _mm_setzero_si128();

    //入力値を設定
    Hoge[0] = 1.0;
    Hoge[1] = 2.0;
    Hoge[2] = 3.0;
    Hoge[3] = 4.0;

    IntHoge[0] = 1;
    IntHoge[1] = 2;
    IntHoge[2] = 3;
    IntHoge[3] = 4;
    
    //ロード＞ストア
    //floatは4byte float配列なら4要素を同時にレジスタに読み込める
    Acc = _mm_load_ps(Hoge);
    _mm_store_ps(Piyo, Acc);

    // int(4byte)のロードストア
    // http://stackoverflow.com/questions/22440536/sse-sum-of-unsigned-long-long-array
    //    __m128i* pa = reinterpret_cast<__m128i *>(IntHoge);
    IntAcc = _mm_load_si128(reinterpret_cast<__m128i*>(&IntHoge));
    _mm_store_si128(reinterpret_cast<__m128i*>(&IntPiyo), IntAcc);
    
        //結果を確認
    for(int i=0; i<4; ++i){
        std::cout << Hoge[i] << std::endl;
        std::cout << Piyo[i] << std::endl;
        std::cout << IntHoge[i] << std::endl;
        std::cout << IntPiyo[i] << std::endl;
    }
}

int main() {
  //sseのデータ型 16byteにアラインメントされたデータ
  __m128 a, b, c;

  //各種intrinsicsを使って4要素を操作する
  //floatはbyte？
  a = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
  b = _mm_setr_ps(5.0f, 6.0f, 7.0f, 8.0f);
  c = _mm_add_ps(a, b);
  c = _mm_mul_ps(c, a);
  c = _mm_sub_ps(c, b);

  float* r = (float*)&c;
  printf("%.2f, %.2f, %.2f, %.2f\n", r[0], r[1], r[2], r[3]);

  examin_loadstore();
}
