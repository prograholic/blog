#include "nested_exception_sample.h"

#include <exception>
#include <stdexcept>

#include <iostream>

struct third_party_exception {
	explicit third_party_exception(int e) : code(e) {
	}

	int code;
};


void third_party_worker() {
	throw third_party_exception(100);
}

class our_exception : public std::runtime_error {
public:
	our_exception(const std::string & e) : std::runtime_error("our error: " + e) {
	}
};

void ourWorker() {
	try {
		third_party_worker();
	} catch (...) {
		throw_with_nested(our_exception("worker failed"));
	}
}

void exceptionHandler(const our_exception & e, bool catchNested) {
	std::cerr << "our exception catched: " << e.what();

	if (catchNested) {
		try {
			rethrow_if_nested(e);
		} catch (const third_party_exception & e) {
			std::cerr << ", low level reason is: " << e.code;
		}
	}

	std::cerr << std::endl;
}

void exceptionProcessing() {
	try {
		ourWorker();
	} catch (const our_exception & e) {
		exceptionHandler(e, false);
	}

	try {
		ourWorker();
	} catch (const our_exception & e) {
		exceptionHandler(e, true);
	}
}




void processNestedException() {
	try {
		throw 10;
	} catch (...) {
		try {
			throw std::nested_exception();
		} catch (const std::nested_exception & e) {
			std::exception_ptr nested = e.nested_ptr();
		}

	}
}











void nestedExceptionSample() {
	exceptionProcessing();
}
