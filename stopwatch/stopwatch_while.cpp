#include <iostream>
#include <chrono>

"""
g++ -stc=c++11　でコンパイル可能
"""
int main()
{
  auto t = 0;
  auto n = 0;
  while ( 100 > n ){
	auto time_point = std::chrono::high_resolution_clock::now() ;
	//計測する処理を入れる
	auto i = 0;
	while ( i < 10000000 ){
	  i = ++i ;
	}
	//ここまで
	auto duration = std::chrono::high_resolution_clock::now() - time_point;

	auto count = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	std::cout << "処理時間:" << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << "[μs]" << std::endl;
	n = ++n;
	t = count + t;
  }
  t = t / 100;
  std::cout << "100回処理平均時間:" << t << "[μs]" << std::endl;
  return 0;
}
