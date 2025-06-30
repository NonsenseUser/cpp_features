#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

std::timed_mutex mtx;

void func1(){
  std::unique_lock lock(mtx);
  std::cout<< "func1 has the lock" << '\n';
  sleep(1);
  std::cout<< "func1 releases the lock" << '\n';
}

void func2(){
  std::unique_lock lock(mtx, std::defer_lock);
  std::cout << "func2 skips locking" << std::endl;
  if (!lock.try_lock_for(std::chrono::milliseconds(250))){
      std::cout<<"func2 gives up on locking"<< std::endl;
  }
  sleep(1);
}

int main(){
  std::jthread t1(func1);
  std::jthread t2(func2);
}
