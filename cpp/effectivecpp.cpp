
#include <iostream>
#include <vector>
#include "effectivecpp.hpp"

#define SquareMulti(x, y) x * x * y

namespace my {

const int testvector::CONST_H_PB;
const int testvector::CONST_H_PV;

testvector::testvector() {
    std::cout << "testvector constructor" << std::endl;
    std::cout << "CONST_H_PV:" << CONST_H_PV << std::endl;
}


}  // namespace my

// defineでマクロを定義する代わりにテンプレートを使ってインライン関数を記述する
template<typename T>
inline T squreMultiWithInline(const T& a, const T&b) {
    return a * a * b;
}


int main() {

    my::testvector tv = my::testvector();
    std::cout << "CONST_H_PB:" << tv.CONST_H_PB << std::endl;


    std::vector<int> vec(5, 0);
    int i = 0;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << i << "=>" << *it << " ";
        if (i == 3) {
            vec.push_back(5);
        }
        i++;
    }
    std::cout << std::endl;
    std::cout << "vec size:" << vec.size() << std::endl;
    i = 0;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << i << "=>" << *it << " ";
        i++;
    }
    std::cout << std::endl;

    std::cout << "#2 enum hack"  << std::endl;
    std::cout << "show effective.hpp" << std::endl;

    std::cout << "#2 defineの罠" << std::endl;
    int a1 = 5, a2 = 5, a3 = 5;
    int b = 10;
    std::cout << "Expected:" << (++a1*a1*b) << std::endl;
    std::cout << "definel:" << SquareMulti(++a2, b) << std::endl;
    std::cout << "inline:" << squreMultiWithInline(++a3, b) << std::endl;
    std::cout
            << "マクロは置き換えるだけなのでxが++aになってしまい、"
            << "++aが2回実行されてしまう"
            << std::endl;
    std::cout << "inline関数を使うとdefineと同様に"
              << "関数呼び出しのオーバーで安全に使える"
              << std::endl;

    return 0;
}
