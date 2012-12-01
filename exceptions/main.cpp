#include "exception_ptr_sample.h"
#include "thread_and_exception.h"
#include "nested_exception_sample.h"
#include "noexcept_sample.h"

int main()
{
	exceptionPtrSample();
	checkThreadAndException();
	nestedExceptionSample();
	noexceptSample();

	return 0;
}
