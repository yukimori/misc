
#include <iostream>
#include <vector>
#include "test_vector.hpp"

namespace my {

const int testvector::CONST_H_PB;
const int testvector::CONST_H_PV;

testvector::testvector() {
    std::cout << "testvector constructor" << std::endl;
    std::cout << "CONST_H_PV:" << CONST_H_PV << std::endl;
}

}  // namespace my

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

    return 0;
}
