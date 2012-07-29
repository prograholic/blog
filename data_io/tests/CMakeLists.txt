project (data_io_tests)

macro(ADD_BOOST_TEST name )
	add_executable(${name} ${ARGV})
	target_link_libraries(${name} ${Boost_LIBRARIES})
	add_test(${name} ${name})
endmacro()



set(DataIoTestsSources
	data_io_tests.cpp
	data_io_tests.h


	data_io_tests_endian.h
	data_io_tests_inserter.h
	data_io_tests_extractor.h
)


ADD_BOOST_TEST(data_io_tests ${DataIoTestsSources})
