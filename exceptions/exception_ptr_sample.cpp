#include <exception>

#include <iostream>


using namespace std;



struct some_exception {
	explicit some_exception(int x): v(x) {
		cout << " int ctor" << endl;
	}

	some_exception(const some_exception & e): v(e.v) {
		cout << " copy ctor" << endl;
	}

	int v;
};

exception_ptr throwExceptionAndCaptureExceptionPtr() {
	exception_ptr currentException;
	try {
		const int throwValue = 10;
		cout << "throwing           " << throwValue << "..." << endl;
		throw some_exception(throwValue);

	} catch (...) {
		 currentException = current_exception();
	}

	return currentException;
}

void rethrowException(exception_ptr ePtr) {
	try {
		if (ePtr) {
			rethrow_exception(ePtr);
		}

	} catch (const some_exception & e) {
		cout << "catched int value: " << e.v << endl;
	}

	exception_ptr anotherExceptionPtr = ePtr;
	try {
		if (anotherExceptionPtr) {
			rethrow_exception(anotherExceptionPtr);
		}

	} catch (const some_exception & e) {
		cout << "catched int value: " << e.v << endl;
	}
}

void checkMakeExceptionPtr() {
	exception_ptr currentException = make_exception_ptr(some_exception(20));
	cout << "exception_ptr constructed" << endl;

	rethrowException(currentException);
}

void exceptionPtrSample() {
	rethrowException(throwExceptionAndCaptureExceptionPtr());
	checkMakeExceptionPtr();
}
