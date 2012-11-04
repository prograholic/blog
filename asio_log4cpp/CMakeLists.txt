cmake_minimum_required(VERSION 2.8)

project (asio_log4cpp)

add_definitions(-std=c++11)


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

set (CommonSources
	common.h
	runnable.h

	connection_manager.cpp
	connection_manager.h

	connection_base.cpp
	connection_base.h

	application.cpp
	application.h
)


add_library(asio_log4cpp_common STATIC ${CommonSources})


set (ServerSources
	server_main.cpp

	server.cpp
	server.h

	server_connection.cpp
	server_connection.h
)




add_executable(asio_log4cpp_server ${ServerSources})


target_link_libraries(asio_log4cpp_server
	${CMAKE_THREAD_LIBS_INIT}
	asio_log4cpp_common
	${Boost_LIBRARIES}
	${LOG4CPP_LIBRARIES}
)



set (ClientSources
	client_main.cpp

	client.cpp
	client.h

	client_connection.cpp
	client_connection.h
)




add_executable(asio_log4cpp_client ${ClientSources})


target_link_libraries(asio_log4cpp_client
	${CMAKE_THREAD_LIBS_INIT}
	asio_log4cpp_common
	${Boost_LIBRARIES}
	${LOG4CPP_LIBRARIES}
)


include(FeatureSummary)
feature_summary(WHAT ALL)
