project (my_stl_tests)

macro(ADD_BOOST_TEST name )
	add_executable(${name} ${ARGV})
	target_link_libraries(${name} ${Boost_LIBRARIES})
	add_test(${name} ${name})
endmacro()



set(AlgorithmTests
	algorithm_tests.cpp
)

remove_definitions(-nostdinc)

ADD_BOOST_TEST(algorithm_tests ${AlgorithmTests})
