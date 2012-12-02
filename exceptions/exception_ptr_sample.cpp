#include <exception>
#include <iostream>

struct some_exception {
	explicit some_exception(int x): v(x) {
		std::cout << " int ctor" << std::endl;
	}

	some_exception(const some_exception & e): v(e.v) {
		std::cout << " copy ctor" << std::endl;
	}

	int v;
};

std::exception_ptr throwExceptionAndCaptureExceptionPtr() {
	std::exception_ptr currentException;
	try {
		const int throwValue = 10;
		std::cout << "throwing           " << throwValue << "..." << std::endl;
		throw some_exception(throwValue);

	} catch (...) {
		 currentException = std::current_exception();
	}

	return currentException;
}

void rethrowException(std::exception_ptr ePtr) {
	try {
		if (ePtr) {
			std::rethrow_exception(ePtr);
		}

	} catch (const some_exception & e) {
		std::cout << "catched int value: " << e.v << std::endl;
	}

	std::exception_ptr anotherExceptionPtr = ePtr;
	try {
		if (anotherExceptionPtr) {
			std::rethrow_exception(anotherExceptionPtr);
		}

	} catch (const some_exception & e) {
		std::cout << "catched int value: " << e.v << std::endl;
	}
}

void checkMakeExceptionPtr() {
	std::exception_ptr currentException = std::make_exception_ptr(some_exception(20));
	std::cout << "exception_ptr constructed" << std::endl;

	rethrowException(currentException);
}

void exceptionPtrSample() {
	rethrowException(throwExceptionAndCaptureExceptionPtr());
	checkMakeExceptionPtr();
}
