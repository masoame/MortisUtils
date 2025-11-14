#include <utils.hpp>

#include<iostream>

int main() 
{
	int i = 0;
	auto task =  [&] {
		std::cout << "Hello, ThreadPool!" << ++i <<  std::endl;
	};

	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	Mo::Thr::Async(task).wait();
	//std::this_thread::sleep_for(std::chrono::seconds(2));
}

extern"C" __declspec(dllexport) void __stdcall masoame() {}