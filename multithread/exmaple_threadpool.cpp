#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

/**
    g++ -std=c++11 exmaple_threadpool.cpp ThreadPool.h  -pthread
    http://d.hatena.ne.jp/nagoya313/20111125/1322231599
 **/

int main() {

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                    std::cout << "hello " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "world " << i << std::endl;
                    return i*i;
                })
                             );
    }

    for (auto && result : results) {
        std::cout << result.get() << ' ';
    }
    std::cout << std::endl;

    return 0;
}
