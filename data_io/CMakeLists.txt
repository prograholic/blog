cmake_minimum_required(VERSION 2.8)

project(data_io)

find_package(Boost COMPONENTS unit_test_framework)


set (DataIoSources
	data_io.cpp

	data_io_common.h
	data_io_slice.h
	data_io_endian.h

	data_io_inserter.h
	data_io_extractor.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(data_io ${DataIoSources})

if(Boost_FOUND)

	include(CTest)

	add_subdirectory(tests)

endif()
