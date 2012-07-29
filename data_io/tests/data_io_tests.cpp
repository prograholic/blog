#define BOOST_TEST_MODULE data_io

#include <boost/test/included/unit_test.hpp>


#include "data_io_endian.h"
#include "data_io_inserter.h"



BOOST_AUTO_TEST_SUITE(endian)

using namespace dio::endian;

BOOST_AUTO_TEST_CASE(test_little_endian_to_int)
{
	char buff[] = {0x00, 0x40};

	BOOST_CHECK_EQUAL(0x4000, le_mem_2_type<dio::uint16_t>(buff));

}


BOOST_AUTO_TEST_CASE(test_big_endian_to_int)
{
	char buff[] = {0x12, 0x34, 0x56, 0x78};

	BOOST_CHECK_EQUAL(0x12345678, be_mem_2_type<dio::uint32_t>(buff));

}


BOOST_AUTO_TEST_CASE(test_little_endian_from_int)
{
	char etalon[] = {0x78, 0x56, 0x34, 0x12};
	dio::uint32_t x = 0x12345678;

	char tmp[sizeof(x)];

	le_type_2_mem(x, tmp);


	BOOST_CHECK_EQUAL_COLLECTIONS(tmp, tmp + sizeof(x), etalon, etalon + sizeof(x));
}


BOOST_AUTO_TEST_CASE(test_big_endian_from_int)
{
	char etalon[] = {0x12, 0x34, 0x56, 0x78};
	dio::uint32_t x = 0x12345678;

	char tmp[sizeof(x)];

	be_type_2_mem(x, tmp);


	BOOST_CHECK_EQUAL_COLLECTIONS(tmp, tmp + sizeof(x), etalon, etalon + sizeof(x));

}

BOOST_AUTO_TEST_SUITE_END()



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
