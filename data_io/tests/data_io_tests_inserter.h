#include "data_io_tests.h"


#include "data_io_inserter.h"



BOOST_AUTO_TEST_SUITE(inserter)

using namespace dio;


BOOST_AUTO_TEST_CASE(test_little_endian_inserter)
{
	data_t x;

	x << as(le, 0x12345678);

	BOOST_CHECK_EQUAL(0x78, x[0]);
	BOOST_CHECK_EQUAL(0x56, x[1]);
	BOOST_CHECK_EQUAL(0x34, x[2]);
	BOOST_CHECK_EQUAL(0x12, x[3]);
}



BOOST_AUTO_TEST_SUITE_END()
