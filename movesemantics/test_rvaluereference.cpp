
#include <iostream>
#include <cmath>
#include <list>

/**
   2011は大きい数値なので、c++03ではtempの中身をコピーし、tempを削除するという動作をした。
   これは処理コストが大きい
 **/
std::list<int> make_big_list1() {
    std::list<int> temp;
    for (size_t i=0; i < 2011; ++i) {
        temp.push_back(i);
    }
    return temp;
}

/**
  tempは削除されるのだからtempの中身を移してしまおうと考えた。
  普通のコピーコンストラクタはconstがついているのでtempを変更できない。
  そこで「近々削除されるなどの理由で中身をはぎ取っても問題ないオブジェクトである」を表すために右辺値参照が作られた
 **/
int main() {
    int &&x = 3;

    std::cout << "&&x:" << x << std::endl;

    int a = 4;
    int b = 2;
    int &&y = a + b;

    std::cout << "&&y:" << y << std::endl;

    double &&z = std::sin(3.14 * 0.5);

    std::cout << "&&z:" << z << std::endl;

    y = std::move(x);

    std::cout << "&&y:" << y << std::endl;
}

