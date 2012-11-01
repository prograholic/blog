cmake_minimum_required(VERSION 2.8)

project (asio_log4cpp)



set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


find_package(Threads REQUIRED)


find_package(PkgConfig REQUIRED)



pkg_search_module(LOG4CPP REQUIRED log4cpp-1.0)
include_directories(${LOG4CPP_INCLUDE_DIRS})
add_definitions(${LOG4CPP_CFLAGS})


set (ProjectSources
	main.cpp

	common.h

	application.cpp
	application.h

	server.cpp
	server.h


)




add_executable(asio_log4cpp ${ProjectSources})


target_link_libraries(asio_log4cpp
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	${LOG4CPP_LIBRARIES}
)


include(FeatureSummary)
feature_summary(WHAT ALL)
