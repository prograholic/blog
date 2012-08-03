project (data_io_tests)

macro(ADD_BOOST_TEST name )
	add_executable(${name} ${ARGV})
	target_link_libraries(${name} ${Boost_LIBRARIES})
	add_test(${name} ${name})
endmacro()



set(DataIoTestsSources
	tests_common.cpp
	tests_common.hpp


	endian_tests.hpp
	inserter_common_tests.hpp
	vector_inserter_tests.hpp
)


ADD_BOOST_TEST(data_io_tests ${DataIoTestsSources})
