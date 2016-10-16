
#include <iostream>

int main() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    std::cout << tp.tv_sec << ", " << tp.tv_nsec << std::endl;

}
