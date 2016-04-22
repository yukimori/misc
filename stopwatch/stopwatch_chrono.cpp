#include <chrono>
#include <iostream>
#include <thread>

/**
   http://codereview.stackexchange.com/questions/14184/c11-generic-stop-watch
   http://vivi.dyndns.org/tech/cpp/timeMeasurement.html
 **/

template<class Period = std::ratio<1,1000> >
class Stopwatch
{
public:
  Stopwatch() {
	restart() ;
  }

public:
  void restart() {
	// 計測時間を保存
	start = std::chrono::high_resolution_clock::now() ;
  }

  double elapsed() {
	return std::chrono::duration_cast<std::chrono::duration<double, Period> >(std::chrono::high_resolution_clock::now() - start).count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

int main()
{
  Stopwatch<> sw;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << sw.elapsed() << std::endl;

  
}
