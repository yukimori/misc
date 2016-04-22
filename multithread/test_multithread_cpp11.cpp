#include <vector>
#include <future>
#include <iostream>

/**
   http://qiita.com/termoshtt/items/d3cb7fe226cdd498d2ef
   g++ -std=c++11 programfile -pthread
 **/

int main(int argc, char const *argv[]) {
  std::vector<int> v(10);
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i) {
    threads.push_back(std::thread([i, &v] { v[i] = i * i; }));
  }
  for (std::thread &th : threads) {
    th.join();
  }
  for (int i : v) {
	std::cout << i << std::endl;
  }
  return 0;
}
