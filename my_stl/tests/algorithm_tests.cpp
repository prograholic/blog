#define BOOST_TEST_MODULE algorithm

#include <boost/test/included/unit_test.hpp>


#include "algorithm.h"


BOOST_AUTO_TEST_SUITE(for_each)

struct run_counter
{
	run_counter(): mRunCounter(0)
	{
	}

	template <typename ValueT>
	void operator () (const ValueT & val)
	{
		++mRunCounter;
	}

	int mRunCounter;
};


BOOST_AUTO_TEST_CASE(empty_container)
{
	int buff[] = {0, 1, 2, 3, 4};
	run_counter rc;
	my_stl::for_each(buff, buff, rc);

	BOOST_CHECK_EQUAL(0, rc.mRunCounter);
}

BOOST_AUTO_TEST_CASE(container_with_5_elements)
{
	int buff[] = {0, 1, 2, 3, 4};
	run_counter rc;
	rc = my_stl::for_each(buff, buff + 5, rc);

	BOOST_CHECK_EQUAL(5, rc.mRunCounter);
}


BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(find)

BOOST_AUTO_TEST_CASE(return_end_if_not_found)
{
	int buff[] = {0, 1, 2, 3, 4};
	int * first = buff;
	int * last = buff + 5;

	int * pos = my_stl::find(first, last, 6);

	BOOST_CHECK_EQUAL(pos, last);
}


BOOST_AUTO_TEST_CASE(return_valid_pos_for_element)
{
	int buff[] = {0, 1, 2, 3, 4};
	int * first = buff;
	int * last = buff + 5;

	int * pos = my_stl::find(first, last, 3);

	BOOST_CHECK_EQUAL(pos, first + 3);
	BOOST_CHECK_EQUAL(3, *pos);
}


BOOST_AUTO_TEST_SUITE_END()
