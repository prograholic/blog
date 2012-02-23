cmake_minimum_required(VERSION 2.8)

project(ProtobufTests)




set (ProtobufTestsSources
	main.cpp
)





find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})


find_package(Threads REQUIRED)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS message.proto)


add_executable(ProtobufTests ${ProtobufTestsSources} ${PROTO_SRCS} ${PROTO_HDRS})


target_link_libraries(ProtobufTests
	${CMAKE_THREAD_LIBS_INIT}
	${PROTOBUF_LIBRARY}
)
