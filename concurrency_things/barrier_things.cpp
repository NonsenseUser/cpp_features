#include <barrier>
#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>

std::atomic<int> a;

void done(){
  std::cout << "everything is done";
}

std::barrier bar(3, done);

void func1(){
  std::cout << "func1 is before the barrier" << std::endl;
  std::cout << "func1 awaits" << std:: endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  bar.arrive_and_wait();
  std::cout << "func1 finished waiting" << std:: endl;
  std::cout << "round 2"<< std::endl;
  bar.arrive_and_wait();
  std::cout<<"func1 finished second wait"<<std::endl;
}

void func2(){
  std::cout <<"func2 is before waiting" <<std::endl;
  bar.arrive_and_drop();
  std::cout << "func2 skipper the barrier";
}

void func3(){
  std::cout<< "func3 is before the barrier" << std::endl;
  //std::this_thread::sleep_for(std::chrono::milliseconds(500));
  bar.arrive_and_wait();
  std::cout << "func3 finished waiting" << std:: endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  bar.arrive_and_wait();
  std::cout<<"func3 finished second wait"<< std::endl;
}

int main(){
  std::jthread t1(func1);
  std::jthread t2(func2);
  std::jthread t3(func3);
}
