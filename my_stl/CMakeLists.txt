cmake_minimum_required(VERSION 2.8)

project(my_stl)

find_package(Boost COMPONENTS unit_test_framework)


set (MyStlSources
	mystdcpp.cpp
	algorithm.h
)


add_definitions(-nostdinc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(mystdc++ SHARED ${MyStlSources})

if(Boost_FOUND)

	include(CTest)

	add_subdirectory(tests)

endif()
