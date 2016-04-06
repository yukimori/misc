#include <boost/thread/thread.hpp>
#include <iostream>
#define MAX 5
 
void
thread_1 () {
  for (int i = 0; i < MAX; i++) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}
void
thread_2 () {
  for (int i = 0; i < MAX; i++) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}
 
int
main(int argc, char const* argv[])
{
  boost::thread th1(thread_1);
  boost::thread th2(thread_2);
 
  th1.join ();
  th2.join ();
 
  return 0;
}
