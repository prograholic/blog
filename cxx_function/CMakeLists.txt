cmake_minimum_required(VERSION 2.8)

project (cxx_function)


add_definitions(-std=c++11)

set (CxxFunctionSources
  main.cpp
)

add_executable(cxx_function ${CxxFunctionSources})
