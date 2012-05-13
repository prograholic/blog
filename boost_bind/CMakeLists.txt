cmake_minimum_required(VERSION 2.8)

project (boost_bind)


set (BoostBindSources
	my_bind.h
	main.cpp
)


set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0" "1.49" "1.49.0")

find_package(Boost "1.47.0" REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(${Boost_DEFINITIONS})




add_executable(boost_bind ${BoostBindSources})
