
#include <iostream>


int main() {
    int a = 0;

    // ポインタをconstで宣言する
    const int* b = &a;
    int const* b = &a;  // 上の行と同義
    // *b = 1;  //error bはconst intへのポインタなので、ポインタの示す先をconstにする

    // ポインタオブジェクトで保持するアドレスを不変にしたい場合
    // bのアドレスが不変
    // *bでアクセスするaの保持している値は書き換えることができる
    int* const b2 = &a; 

    /* const参照 */
    int a3 = 10;
    const int& b3 = a;
    // b = 20;  // エラー:bはconst修飾されている

    // int& const b4 = a; エラー
}
