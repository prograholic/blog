#include <exception>
#include <stdexcept>
#include <thread>
#include <future>
#include <iostream>


using namespace std;

void worker(promise<void> & p) {
	try {
		throw runtime_error("exception from thread");
	} catch (...) {
		p.set_exception(current_exception());
	}
}

void checkThreadAndException() {
	promise<void> p;
	auto result = p.get_future();

	thread t(worker, ref(p));
	t.detach();

	try {
		result.get();
	} catch (const runtime_error & e) {
		cout << "runtime error catched from async worker" << endl;
	}
}
