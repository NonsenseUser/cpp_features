#include <mutex>
#include <shared_mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

std::condition_variable cv;
std::shared_mutex m;
bool ready = false;

void func0(){
  std::unique_lock<std::shared_mutex> lk;
  std::cout<<"func0 acquires the lock"<<std::endl;
  cv.wait(lk, [](){return ready;);
  std::cout<<"func0 finished waiting"<< std::endl;
}
void func1(){
  std::shared_lock<std::shared_mutex> lock;
  std::cout<<"func1 shares the lock"<<std::endl;
  sleep(1);
  std::cout<<"func1 releases the lock"<<std::endl;
} 
void func2(){
  std::shared_lock<std::shared_mutex> lock;
  std::cout<<"func2 shares the lock"<<std::endl;
  sleep(1);
  std::cout<<"func2 releases the lock"<< std::endl;
} 
void func3(){
  std::shared_lock<std::shared_mutex> lock;
  std::cout<<"func3 shares the lock"<<std::endl;
  sleep(1);
  std::cout<<"func3 releases the lock"<< std::endl;
} 
int main(){
  std::jthread t1(func1);
  std::jthread t2(func2);
  std::jthread t3(func3);
}
