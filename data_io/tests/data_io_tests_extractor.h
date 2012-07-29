#ifndef DATA_IO_TESTS_EXTRACTOR_H
#define DATA_IO_TESTS_EXTRACTOR_H

#include "data_io_tests.h"

#include "data_io_extractor.h"
#include "data_io_inserter.h"


BOOST_AUTO_TEST_SUITE(extractor)

using namespace dio;


BOOST_AUTO_TEST_CASE(extract_le_int)
{
	data_t x;
	uint32_t val = 0x12345678;
	x << as(le, val);

	BOOST_REQUIRE_EQUAL(4, x.size());

	uint32_t testVal;
	x >> as(le, &testVal);

	BOOST_CHECK_EQUAL(val, testVal);
}



BOOST_AUTO_TEST_SUITE_END()


#endif /* DATA_IO_TESTS_EXTRACTOR_H */
