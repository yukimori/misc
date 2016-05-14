#include <iostream>

template <int N>
struct Factorial {
    enum { value = N * Factorial<N - 1>::value };
};
template <>
struct Factorial<0> {
    enum { value = 1 };
};

// Factorial<4>::value == 24
// Factorial<0>::value == 1
void foo() {
    int x = Factorial<12>::value; // == 24
    int y = Factorial<0>::value; // == 1
    
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

int main() {
    foo();
}
