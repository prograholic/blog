project (data_io_tests)

macro(ADD_BOOST_TEST name )
	add_executable(${name} ${ARGV})
	target_link_libraries(${name} ${Boost_LIBRARIES})
	add_test(${name} ${name})
endmacro()



set(DataIoTestsSources
	data_io_tests.cpp
)


ADD_BOOST_TEST(data_io_tests ${DataIoTestsSources})
