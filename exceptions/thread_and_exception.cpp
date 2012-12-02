#include <exception>
#include <stdexcept>
#include <thread>
#include <future>
#include <iostream>

void worker(std::promise<void> & p) {
	try {
		throw std::runtime_error("exception from thread");
	} catch (...) {
		p.set_exception(std::current_exception());
	}
}

void checkThreadAndException() {
	std::promise<void> p;
	auto result = p.get_future();

	std::thread t(worker, ref(p));
	t.detach();

	try {
		result.get();
	} catch (const std::runtime_error & e) {
		std::cout << "runtime error catched from async worker" << std::endl;
	}
}
