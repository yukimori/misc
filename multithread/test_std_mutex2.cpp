#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

/**
  http://minus9d.hatenablog.com/entry/20130914/1379168684
 **/

void worker() {
  std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
}

//あるスレッドが出力している間に、他のスレッドが割り込み表示が乱れることがある
int nouse_mutex() {
  std::cout << "if nouse mutex, thread interrupt other thread ouput..." << std::endl;

  // make 4 threads
  std::vector<std::thread> ths(4);
  for (auto& th : ths) {
	th = std::thread(worker);
  }

  // waif for all thread are finished
  for (auto& th : ths) {
	th.join();
  }

  return 0;
}

std::mutex mtx;
//スレッドが占有して資源を使用すべき処理の前後をlock()とunlock()で囲う
int worker_with_lock() {
  //ここでは標準出力が共通資源。使う前にロック
  mtx.lock();
  std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
  //unlockを忘れると他スレッドの処理が止まる
  mtx.unlock();
}

//lockを使って乱れなく表示できる版
int use_mutex() {
  std::cout << "if use mutex. No interrupted" << std::endl;

  // make 4 threads
  std::vector<std::thread> ths(4);
  for (auto& th : ths) {
	th = std::thread(worker_with_lock);
  }

  // waif for all thread are finished
  for (auto& th : ths) {
	th.join();
  }

  return 0;
}


// lock_guardを使うと明示的にlock()とunlock()を呼ぶ必要がなくなる
int worker_with_lockguard() {
  // lock_guardを使うととスコープの終わりでlock()変数が破棄され、自動的にロックも解除される
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "thread id:" << std::this_thread::get_id() << std::endl;

  return 0;
}

void worker_with_input(int num1, int num2) {
  std::cout << num1 << std::endl;
  std::cout << num2 << std::endl;
}

int use_lockguard() {
  std::cout << "If use lock_guard, unnessesary write to lock()/unlock()" << std::endl;

  // make 4 threads
  std::vector<std::thread> ths(4);
  for (auto& th : ths) {
	th = std::thread(worker_with_lockguard);
  }

  // waif for all thread are finished
  for (auto& th : ths) {
	th.join();
  }

  return 0;
}

int use_input() {
  std::thread th(worker_with_input, 10, 100);
  th.join();

  return 0;
}

int main() {
  nouse_mutex();
  use_mutex();
  use_lockguard();
  use_input();
  return 0;
}

