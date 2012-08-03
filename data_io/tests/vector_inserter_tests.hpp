#ifndef BOOST_DIO_VECTOR_INSERTER_TESTS_HPP
#define BOOST_DIO_VECTOR_INSERTER_TESTS_HPP

#include "tests_common.hpp"

#include <boost/dio/vector_inserter.hpp>

BOOST_AUTO_TEST_SUITE(vector_inserter)

using namespace boost::dio;
using namespace boost;


BOOST_AUTO_TEST_CASE(check_simple_insert)
{
  std::vector<uint8_t> holder;

  holder << 1 << 2 << 3 << 4;

  BOOST_REQUIRE_EQUAL(4, holder.size());

  BOOST_CHECK_EQUAL(1, holder[0]);
  BOOST_CHECK_EQUAL(2, holder[1]);
  BOOST_CHECK_EQUAL(3, holder[2]);
  BOOST_CHECK_EQUAL(4, holder[3]);
}


BOOST_AUTO_TEST_CASE(check_endian_insert)
{
  std::vector<uint8_t> holder;

  uint16_t val1 = 0x1234;
  uint32_t val2 = 0x56789012;

  holder << as(le, val1) << as(be, val2);

  BOOST_REQUIRE_EQUAL(6, holder.size());

  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);

  BOOST_CHECK_EQUAL(0x56, holder[2]);
  BOOST_CHECK_EQUAL(0x78, holder[3]);
  BOOST_CHECK_EQUAL(0x90, holder[4]);
  BOOST_CHECK_EQUAL(0x12, holder[5]);
}


BOOST_AUTO_TEST_CASE(check_explicit_cast_for_endian_insert)
{
  std::vector<uint8_t> holder;

  holder << as<uint16_t>(le, 0x1234) << as<uint32_t>(be, 0x56789012) << as<uint64_t>(le, static_cast<uint16_t>(0x1234));

  BOOST_REQUIRE_EQUAL(2 + 4 + 8, holder.size());

  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);

  BOOST_CHECK_EQUAL(0x56, holder[2]);
  BOOST_CHECK_EQUAL(0x78, holder[3]);
  BOOST_CHECK_EQUAL(0x90, holder[4]);
  BOOST_CHECK_EQUAL(0x12, holder[5]);

  BOOST_CHECK_EQUAL(0x34, holder[6]);
  BOOST_CHECK_EQUAL(0x12, holder[7]);
  BOOST_CHECK_EQUAL(0x00, holder[8]);
  BOOST_CHECK_EQUAL(0x00, holder[9]);
  BOOST_CHECK_EQUAL(0x00, holder[10]);
  BOOST_CHECK_EQUAL(0x00, holder[11]);
  BOOST_CHECK_EQUAL(0x00, holder[12]);
  BOOST_CHECK_EQUAL(0x00, holder[13]);
}



BOOST_AUTO_TEST_CASE(check_vector_insert)
{

  std::vector<uint8_t> holder;
  std::vector<int8_t> input;

  /// fill input with previously checked operators
  holder << as<uint16_t>(le, 0x1234);
  input << 0x56 << 0x78 << 0x90;

  holder << input;

  BOOST_REQUIRE_EQUAL(2 + 3, holder.size());
  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);
  BOOST_CHECK_EQUAL(0x56, holder[2]);
  BOOST_CHECK_EQUAL(0x78, holder[3]);
  BOOST_CHECK_EQUAL(0x90, holder[4]);
}



BOOST_AUTO_TEST_CASE(check_simple_array_insert)
{
  std::vector<uint8_t> holder;
  char data [8] = {0, 1, 2, 3, 4, 5, 6, 7};

  /// fill input with previously checked operators
  holder << as<uint16_t>(le, 0x1234);

  holder << data;

  BOOST_REQUIRE_EQUAL(2 + 8, holder.size());
  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);
  BOOST_CHECK_EQUAL(0, holder[2]);
  BOOST_CHECK_EQUAL(1, holder[3]);
  BOOST_CHECK_EQUAL(2, holder[4]);
  BOOST_CHECK_EQUAL(3, holder[5]);
  BOOST_CHECK_EQUAL(4, holder[6]);
  BOOST_CHECK_EQUAL(5, holder[7]);
  BOOST_CHECK_EQUAL(6, holder[8]);
  BOOST_CHECK_EQUAL(7, holder[9]);
}



BOOST_AUTO_TEST_CASE(check_boost_array_insert)
{
  std::vector<uint8_t> holder;
  boost::array<int8_t, 8> data = {{0, 1, 2, 3, 4, 5, 6, 7}};

  /// fill input with previously checked operators
  holder << as<uint16_t>(le, 0x1234);

  holder << data;

  BOOST_REQUIRE_EQUAL(2 + 8, holder.size());
  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);
  BOOST_CHECK_EQUAL(0, holder[2]);
  BOOST_CHECK_EQUAL(1, holder[3]);
  BOOST_CHECK_EQUAL(2, holder[4]);
  BOOST_CHECK_EQUAL(3, holder[5]);
  BOOST_CHECK_EQUAL(4, holder[6]);
  BOOST_CHECK_EQUAL(5, holder[7]);
  BOOST_CHECK_EQUAL(6, holder[8]);
  BOOST_CHECK_EQUAL(7, holder[9]);
}



BOOST_AUTO_TEST_CASE(check_range_insert)
{
  std::vector<uint8_t> holder;
  char data [] = {0x12, 0x34, 0x56, 0x78, 0x90};

  /// fill input with previously checked operators
  holder << as<uint16_t>(le, 0x1234);

  holder << make_range(data + 1, data + 4); /// insert 3 elements

  BOOST_REQUIRE_EQUAL(2 + 3, holder.size());
  BOOST_CHECK_EQUAL(0x34, holder[0]);
  BOOST_CHECK_EQUAL(0x12, holder[1]);
  BOOST_CHECK_EQUAL(0x34, holder[2]);
  BOOST_CHECK_EQUAL(0x56, holder[3]);
  BOOST_CHECK_EQUAL(0x78, holder[4]);
}


BOOST_AUTO_TEST_SUITE_END()



#endif /* BOOST_DIO_VECTOR_INSERTER_TESTS_HPP */
