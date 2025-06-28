#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

atomic<int> a = 0;

void func(){
  int b = a.exchange(1);
  std::cout << "b = "<< b << endl;
}

void func1(){
  cout << "before: a = "<< a << endl;
  int i = 1;
  cout << "i = "<< i << endl;
  a.compare_exchange_strong(i, 5);
  cout << "after: a = "<< a << endl;
  cout << "i = "<< i << endl;
}

void func2(){
  int i = 2;
  cout << "before: a = "<< a << endl;
  cout << "i = "<< i<< endl;
  a.compare_exchange_strong(i, 10);
  cout << "after: a = "<< a << endl;
  cout << "i = "<< i<< endl;
}

int main(){
  jthread t(func);
  sleep(1);
  cout << "a = " << a << endl;
  thread t1(func1);
  t1.join();

  thread t2(func2);
  t2.join();

}
