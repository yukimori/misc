#include <iostream>
#include <boost/thread.hpp>
using namespace std;
using namespace boost;
 
// 引数なし関数をマルチスレッドで実行
 
const int kCount =  100000000;
const int kInterval = 1000000;
 
void PrintHello() {
  for(int i = 0; i != kCount; ++i)
    if (!(i % kInterval)) cout << "Hello ";
}
 
void PrintWorld() {
  for(int i = 0; i != kCount; ++i)
    if (!(i % kInterval)) cout << "World! ";
}
 
int main() {
  thread thr_hello(&PrintHello); // PrintHello関数を実行するスレッドの生成、実行
  thread thr_world(&PrintWorld);
 
  thr_hello.join(); // thr_helloが走らせているスレッドの終了を待つ
  thr_world.join();
  return 0;
}
