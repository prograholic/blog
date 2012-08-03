#ifndef BOOST_DIO_ENDIAN_TESTS_HPP
#define BOOST_DIO_ENDIAN_TESTS_HPP

#include "tests_common.hpp"


#include "boost/dio/endian.hpp"

BOOST_AUTO_TEST_SUITE(endian_data_to_int)

using namespace boost::dio;
using namespace boost::dio::endian;


BOOST_AUTO_TEST_CASE(test_little_endian_to_int)
{
  char buff[] = {0x12, 0x34, 0x56, 0x78};

  BOOST_CHECK_EQUAL(0x78563412, to_little_endian<uint32_t>(buff));

  BOOST_CHECK_EQUAL(0x78563412, to_little_endian<uint32_t>(buff, buff + 4));

  BOOST_CHECK_THROW(to_little_endian<uint32_t>(buff, buff + 3), dio_exception);

}


BOOST_AUTO_TEST_CASE(test_big_endian_to_int)
{
  char buff[] = {0x12, 0x34, 0x56, 0x78};

  BOOST_CHECK_EQUAL(0x12345678, to_big_endian<uint32_t>(buff));

  BOOST_CHECK_EQUAL(0x12345678, to_big_endian<uint32_t>(buff, buff + 4));

  BOOST_CHECK_THROW(to_big_endian<uint32_t>(buff, buff + 3), dio_exception);

}



BOOST_AUTO_TEST_CASE(test_native_endian_to_int)
{
  char buff[] = {0x12, 0x34, 0x56, 0x78};

  BOOST_CHECK_THROW(to_native_endian<uint32_t>(buff, buff + 3), dio_exception);

#if defined(BOOST_LITTLE_ENDIAN)

  BOOST_CHECK_EQUAL(0x78563412, to_native_endian<uint32_t>(buff));
  BOOST_CHECK_EQUAL(0x78563412, to_native_endian<uint32_t>(buff, buff + 4));

#elif defined (BOOST_BIG_ENDIAN)

  BOOST_CHECK_EQUAL(0x12345678, to_native_endian<uint32_t>(buff));
  BOOST_CHECK_EQUAL(0x12345678, to_native_endian<uint32_t>(buff, buff + 4));

#else
  #error "Cannot determine endian type, see boost/detail/endian.hpp for details"
#endif


}




BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(endian_int_to_data)

using namespace boost::dio;
using namespace boost::dio::endian;


BOOST_AUTO_TEST_CASE(test_int_to_little_endian)
{
  const char etalon[4] = {0x12, 0x34, 0x56, 0x78};

  char data[4];

  uint32_t x = 0x78563412;

  char * ptr = from_little_endian(x, data);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data));
  ptr = from_little_endian(x, data, data + 4);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(from_little_endian(x, data, data + 3), dio_exception);

}


BOOST_AUTO_TEST_CASE(test_int_to_big_endian)
{
  const char etalon[4] = {0x12, 0x34, 0x56, 0x78};

  char data[4];

  uint32_t x = 0x12345678;

  char * ptr = from_big_endian(x, data);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data));
  ptr = from_big_endian(x, data, data + 4);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(from_big_endian(x, data, data + 3), dio_exception);

}



BOOST_AUTO_TEST_CASE(test_int_to_native_endian)
{
  char data[4];

  uint32_t x = 0x78563412;


#if defined(BOOST_LITTLE_ENDIAN)

  const char etalon[4] = {0x12, 0x34, 0x56, 0x78};

#elif defined (BOOST_BIG_ENDIAN)

  const char etalon[4] = {0x78, 0x56, 0x34, 0x12};

#else
  #error "Cannot determine endian type, see boost/detail/endian.hpp for details"
#endif



  char * ptr = from_native_endian(x, data);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  memset(data, 0, sizeof(data));
  ptr = from_native_endian(x, data, data + 4);
  BOOST_CHECK((data + 4) == ptr); // points to the end of data;
  BOOST_CHECK_EQUAL_COLLECTIONS(etalon, etalon + 4, data, data + 4);

  BOOST_CHECK_THROW(from_native_endian(x, data, data + 3), dio_exception);
}


BOOST_AUTO_TEST_SUITE_END()


#endif /* BOOST_DIO_ENDIAN_TESTS_HPP */
