#include <utils.hpp>

#include<iostream>

int main() 
{
	int i = 0;
	auto task =  [&] {
		std::cout << "Hello, ThreadPool!" << ++i <<  std::endl;
	};

	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	Mo::Thread::Async(task).wait();
	//std::this_thread::sleep_for(std::chrono::seconds(2));
}
