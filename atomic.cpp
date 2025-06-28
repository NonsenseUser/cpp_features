#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> atm_cnt = 0; // Shared variable
int plain_cnt = 0;
int atm_ref_cnt = 0;
std::atomic_ref<int> atm_ref(atm_ref_cnt);

void increment() {
  for (int i = 0; i < 100000; ++i) {
    atm_cnt.fetch_add(1);
    ++plain_cnt;
    ++atm_ref;
  }
}

int main() {
  std::thread t1(increment);
  std::thread t2(increment);

  t1.join();
  t2.join();

  std::cout << "Final atm_cnt value: " << atm_cnt << std::endl;
  std::cout <<"Final plain_cnt value:" << plain_cnt << std::endl; 
  std::cout <<"Final atm_ref_cnt value:" << atm_ref_cnt << std::endl; 
  return 0;
}
