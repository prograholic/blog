cmake_minimum_required(VERSION 2.8)

project(ProtobufTests)



find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Threads REQUIRED)


find_package(Boost REQUIRED)



set (ProtobufTestsProtoSources
	Message.proto
	ServerStatus.proto
	Echo.proto
)

set (ProtobufTestsSources
	main.cpp
	MessageDispatcher.cpp
	MessageDispatcher.h

	ServerStatusMessageProcessor.cpp
	ServerStatusMessageProcessor.h

	EchoMessageProcessor.cpp
	EchoMessageProcessor.h

	${ProtobufTestsProtoSources}
)




PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})


add_executable(ProtobufTests ${ProtobufTestsSources} ${PROTO_SRCS} ${PROTO_HDRS})


target_link_libraries(ProtobufTests
	${CMAKE_THREAD_LIBS_INIT}
	${PROTOBUF_LIBRARY}
)
