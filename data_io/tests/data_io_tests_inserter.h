#ifndef DATA_IO_TESTS_INSERTER_H
#define DATA_IO_TESTS_INSERTER_H

#include "data_io_tests.h"


#include "data_io_inserter.h"



BOOST_AUTO_TEST_SUITE(inserter)

using namespace dio;


BOOST_AUTO_TEST_CASE(test_little_endian_inserter)
{
	data_t x;

	x << as(le, 0x12345678);

	BOOST_REQUIRE_EQUAL(4, x.size());

	BOOST_CHECK_EQUAL(0x78, x[0]);
	BOOST_CHECK_EQUAL(0x56, x[1]);
	BOOST_CHECK_EQUAL(0x34, x[2]);
	BOOST_CHECK_EQUAL(0x12, x[3]);
}

BOOST_AUTO_TEST_CASE(test_big_endian_inserter)
{
	data_t x;

	x << as(be, 0x12345678);

	BOOST_REQUIRE_EQUAL(4, x.size());

	BOOST_CHECK_EQUAL(0x12, x[0]);
	BOOST_CHECK_EQUAL(0x34, x[1]);
	BOOST_CHECK_EQUAL(0x56, x[2]);
	BOOST_CHECK_EQUAL(0x78, x[3]);
}


BOOST_AUTO_TEST_CASE(test_native_int_inserter)
{
	uint32_t intValue;
	uint8_t intValueHolder[sizeof(intValue)] = {0x12, 0x34, 0x56, 0x78};


	memcpy(&intValue, intValueHolder, sizeof(intValue));
	/// intValue may be equal 0x12345678 or 0x78563412, it depends on endianness of host system

	data_t x;
	x << as(native, intValue);

	BOOST_REQUIRE_EQUAL(4, x.size());

	BOOST_CHECK_EQUAL(0x12, x[0]);
	BOOST_CHECK_EQUAL(0x34, x[1]);
	BOOST_CHECK_EQUAL(0x56, x[2]);
	BOOST_CHECK_EQUAL(0x78, x[3]);
}



BOOST_AUTO_TEST_CASE(test_container_inserter)
{
	data_t x;

	data_t y;
	y.push_back(0x12);
	y.push_back(0x34);
	y.push_back(0x56);

	x << y;

	BOOST_CHECK_EQUAL_COLLECTIONS(x.begin(), x.end(), y.begin(), y.end());
}


BOOST_AUTO_TEST_CASE(test_slice_inserter)
{
	data_t x;
	data_t y;
	y << 0x12 << 0x34 << 0x56 << 0x78;

	x << make_out_slice(y, 1, 3);

	BOOST_REQUIRE_EQUAL(3, x.size());

	BOOST_CHECK_EQUAL(0x34, x[0]);
	BOOST_CHECK_EQUAL(0x56, x[1]);
	BOOST_CHECK_EQUAL(0x78, x[2]);
}


BOOST_AUTO_TEST_CASE(test_slice_inserter_with_custom_adapter)
{
	data_t x;
	data_t y;
	y << 0x12 << 0x34 << 0x56 << 0x78;

	x << make_out_slice<fit_to_data_adapter>(y, 1, 100);

	BOOST_REQUIRE_EQUAL(3, x.size());

	BOOST_CHECK_EQUAL(0x34, x[0]);
	BOOST_CHECK_EQUAL(0x56, x[1]);
	BOOST_CHECK_EQUAL(0x78, x[2]);
}




BOOST_AUTO_TEST_SUITE_END()



#endif /* DATA_IO_TESTS_INSERTER_H */
