#ifndef BOOST_DIO_VECTOR_INSERTER_TESTS_HPP
#define BOOST_DIO_VECTOR_INSERTER_TESTS_HPP

#include "tests_common.hpp"

#include <boost/dio/vector_inserter.hpp>

BOOST_AUTO_TEST_SUITE(vector_inserter)

using namespace boost::dio;


BOOST_AUTO_TEST_CASE(check_simple_insert)
{
  std::vector<boost::uint8_t> holder;

  holder << 1 << 2 << 3 << 4;

  BOOST_REQUIRE_EQUAL(4, holder.size());

  BOOST_CHECK_EQUAL(1, holder[0]);
  BOOST_CHECK_EQUAL(2, holder[1]);
  BOOST_CHECK_EQUAL(3, holder[2]);
  BOOST_CHECK_EQUAL(4, holder[3]);
}


BOOST_AUTO_TEST_SUITE_END()



#endif /* BOOST_DIO_VECTOR_INSERTER_TESTS_HPP */
