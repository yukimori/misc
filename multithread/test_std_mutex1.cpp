#include <iostream>
#include <thread>
#include <exception>
#include <mutex>
#include <vector>
#include <ctime>

/**
   http://kaworu.jpn.org/cpp/std::mutex
 **/

using namespace std;
//std::mutexは非再帰的mutex
std::mutex m;
std::vector<time_t> v;

void do_worker1() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  m.lock();
  v.push_back(time(NULL));
  m.unlock();
}

int main(int argc, char *argv[]) {
  try {
	std::thread t1(do_worker1);
	std::thread t2(do_worker1);
	t1.join();
	t2.join();
	for(auto t:v) {
	  std::cout << t << std::endl;
	}
  } catch(std::exception &ex) {
	cerr << ex.what() << endl;
  }
  return(0);
}
