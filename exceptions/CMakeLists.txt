cmake_minimum_required(VERSION 2.8)

project (cxx_exceptions)


find_package(Threads REQUIRED)


add_definitions(-std=c++11)

set (CxxExceptionSources
	main.cpp

	exception_ptr_sample.cpp
	exception_ptr_sample.h

	thread_and_exception.cpp
	thread_and_exception.h

	nested_exception_sample.cpp
	nested_exception_sample.h
)

add_executable(cxx_exceptions ${CxxExceptionSources})



target_link_libraries(cxx_exceptions ${CMAKE_THREAD_LIBS_INIT})
