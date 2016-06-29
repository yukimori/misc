
#include <iostream>
#include <string>

/**
   ref:
   http://yohhoy.hatenablog.jp/entry/2012/12/15/120839
   http://brain.cc.kogakuin.ac.jp/~kanamaru/lecture/C++2/09/09-03.html
   
   まだ途中までしかテストコードを記述していない
 **/
int main() {
    int i1 = 1;
    int i2 = 2;

    std::string s1 = "apple";
    std::string s2 = "banana";

    std::vector<int> v1;
    std::vector<int> v2 = {1, 2, 3, 4};

    // 代入は変数の中身をコピーするというセマンティクスをもつ
    // 文字列のコピー処理はコピー元+コピー先で2倍のメモリ領域が必要となる
    // コンテナの場合は全要素値について個々にコピーが必要
    i1 = i2; // i1==i2==2
    s1 = s2; // s1==s2=="banana"
    v1 = v2; // v1==v2=={1, 2, 3, 4}


    std::unique_str<int> p1(int new(42));
    std::unique_str<int> p2;
    //    p2 = p1; // 代入シンタックスはコピーを表す。unique_strはコピー不可のためコンパイルエラーになる
    // ムーブ代入シンタックスにより、p1からp2へ所有権の移動
    p2 = std::move(p1);

    
}
