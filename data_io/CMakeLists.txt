cmake_minimum_required(VERSION 2.8)

project(data_io)

find_package(Boost COMPONENTS unit_test_framework)


set (DataIoSources
	data_io.cpp
	data_io_common.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(data_io ${MyStlSources})

if(Boost_FOUND)

	include(CTest)

	add_subdirectory(tests)

endif()
