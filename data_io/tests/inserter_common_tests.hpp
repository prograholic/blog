#ifndef BOOST_DIO_INSERTER_COMMON_TESTS_HPP
#define BOOST_DIO_INSERTER_COMMON_TESTS_HPP

#include "tests_common.hpp"

#include <boost/dio/inserter_common.hpp>

BOOST_AUTO_TEST_SUITE(endian_data_to_int)

using namespace boost::dio;
//using namespace boost::dio::endian;


BOOST_AUTO_TEST_CASE(check_little_endian_inserter)
{
  const char etalon [] = {0x78, 0x56, 0x34, 0x12};

  char data [4];

  uint32_t x = 0x12345678;


  char * ptr = as(le, x).insert(data); // check unsafe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data)); // to ensure, that data is different
  ptr = as(le, x).insert(data, data + 4); // check safe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(as(le, x).insert(data, data + 3), dio_exception);
}

BOOST_AUTO_TEST_CASE(check_big_endian_inserter)
{
  const char etalon [] = {0x12, 0x34, 0x56, 0x78};

  char data [4];

  uint32_t x = 0x12345678;


  char * ptr = as(be, x).insert(data); // check unsafe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data)); // to ensure, that data is different
  ptr = as(be, x).insert(data, data + 4); // check safe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(as(be, x).insert(data, data + 3), dio_exception);
}


BOOST_AUTO_TEST_CASE(check_native_endian_inserter)
{
#if defined(BOOST_LITTLE_ENDIAN)

  const char etalon[4] = {0x78, 0x56, 0x34, 0x12};

#elif defined (BOOST_BIG_ENDIAN)

  const char etalon[4] = {0x12, 0x34, 0x56, 0x78};

#else
  #error "Cannot determine endian type, see boost/detail/endian.hpp for details"
#endif

  char data [4];

  uint32_t x = 0x12345678;


  char * ptr = as(ne, x).insert(data); // check unsafe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data)); // to ensure, that data is different
  ptr = as(ne, x).insert(data, data + 4); // check safe version
  BOOST_CHECK((data + 4) == ptr); // points after last element
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(as(ne, x).insert(data, data + 3), dio_exception);
}


BOOST_AUTO_TEST_SUITE_END()



#endif /* BOOST_DIO_INSERTER_COMMON_TESTS_HPP */
