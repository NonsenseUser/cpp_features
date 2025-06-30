#include<chrono>
#include <iostream>
#include <thread>
#include <future>

int i = 0;
int incr(){
  return i+1;
}

void func0(std::packaged_task<int()> task){
  task();
  std::cout<<"i = "<< i<< std::endl;
  sleep(1);

}
void func(std::packaged_task<int()> task){
  std::cout<<" i = "<<i<<std::endl;
  task.make_ready_at_thread_exit();
  std::cout<<"i = "<< i<< std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
int main(){
  std::packaged_task<int()> task(incr);
  std::future<int> fut = task.get_future();
  std::jthread t(func0, std::move(task)); 
  std::cout<<"Result is "<< fut.get()<<std::endl; 

  std::packaged_task<int()> task2(incr);
  std::future<int> fut2 = task2.get_future();
  std::jthread t1(func, std::move(task2));
  if (fut2.wait_for(std::chrono::seconds(1)) != std::future_status::timeout){
    std::cout<<"Result is "<< fut2.get() <<std::endl;
  } else {std::cout<< "timeout \n "<< fut2.get();
  }
}
