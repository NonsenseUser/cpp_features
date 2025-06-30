#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

std::condition_variable cv;
std::mutex m;
bool ready = false;

void func0(){
  std::unique_lock<std::mutex> lk(m);
  std::cout<<"func0 acquires the lock"<<std::endl;
  cv.wait(lk, []{return ready;});
  std::cout<<"func0 finished waiting"<< std::endl;
}
int main(){
  std::jthread t(func0);
  {
    sleep(1);
    std::cout<<"main thread acquire the lock"<<std::endl;
    std::lock_guard<std::mutex> lk(m);
ready = true;
    cv.notify_one();
  }
}
