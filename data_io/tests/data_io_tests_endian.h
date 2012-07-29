#ifndef DATA_IO_TESTS_ENDIAN_H
#define DATA_IO_TESTS_ENDIAN_H

#include "data_io_tests.h"


#include "data_io_endian.h"

BOOST_AUTO_TEST_SUITE(endian)

using namespace dio::endian;

BOOST_AUTO_TEST_CASE(test_little_endian_to_int)
{
	char buff[] = {0x12, 0x34, 0x56, 0x78};

	BOOST_CHECK_EQUAL(0x78563412, le_mem_2_type<dio::uint32_t>(buff));

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


#endif /* DATA_IO_TESTS_ENDIAN_H */
