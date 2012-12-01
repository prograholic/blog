cmake_minimum_required(VERSION 2.8)

project (cxx_exceptions)


add_definitions(-std=c++11)

set (CxxExceptionSources
	main.cpp

	exception_ptr_sample.cpp
	exception_ptr_sample.h
)

add_executable(cxx_exceptions ${CxxExceptionSources})
