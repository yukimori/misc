#include <iostream>

int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

void foo()
{
    int x = factorial(12); // == (4 * 3 * 2 * 1) == 24
    int y = factorial(0); // == 0! == 1

    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

int main() {
    foo();            
}
