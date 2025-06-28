#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

atomic<int> a = 0;
atomic<int> b = 0;

void func(atomic<int>& a, atomic<int>& b){
std::cout<< a << " = "<< b << endl;
std::cout<< "a waits" << endl;
  a.wait(b);
  std::cout<< "after:" << endl;
  std::cout<<"a = "<< a << std::endl;
  std::cout<<"b = "<< b << std::endl; 
}

void func2(atomic<int> &a, atomic<int>& b){
  this_thread::sleep_for(chrono::milliseconds(100));
  std::cout << "previously: b = "<< b << std::endl;
  a.fetch_add(1);
  a.notify_one();
}

int main(){
  thread t(func, ref(a), ref(b));
  thread t2(func2, ref(a), ref(b));
  t.join();
  t2.join();
}
