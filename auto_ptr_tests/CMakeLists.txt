cmake_minimum_required(VERSION 2.8)

project (smart_ptrs)

set (smart_ptrs_sources
    main.cpp
    SimpleClass.cpp
    SimpleClass.h
    ClassOwner.cpp
    ClassOwner.h
)


add_executable(smart_ptrs ${smart_ptrs_sources})
