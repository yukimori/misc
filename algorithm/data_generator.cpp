#include <iostream>
#include <random>

using namespace std;

int main() {
  mt19937 mt(0);
  uniform_int_distribution<int> dist(1, 100000);
  for (int i = 0; i < 100000; ++i) {
    cout << dist(mt) << " " << dist(mt) << endl;
  }
}
