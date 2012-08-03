
//  (C) Copyright Alexey Kutumov 2012.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://github.com/prograholic/blog/tree/master/data_io for most recent version.


#ifndef BOOST_DIO_ENDIAN_HPP
#define BOOST_DIO_ENDIAN_HPP

#include <boost/detail/endian.hpp>

#include <boost/type_traits/make_unsigned.hpp>
#include <boost/throw_exception.hpp>

#include <boost/dio/common.hpp>


namespace boost {

  namespace dio {

    namespace endian {

      /**
       * Performs conversion to little endian.
       *
       * This function does not check iterator validity,
       * use this only if you sure that iterator remains valid.
       *
       * For example:
       * char data[4] = {0x01, 0x02, 0x03, 0x04};
       *
       * uint32_t val = to_little_endian<uint32_t>(data);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_little_endian(InputIteratorT input)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;
        unsigned_t val = 0;

        size_t count = 0;

        while (count < sizeof(val))
        {
          unsigned_t byteElem = static_cast<uint8_t>(*input);
          val |= (byteElem << (CHAR_BIT * count));

          ++input;
          ++count;
        }

        return val;
      }


      /**
       * Performs conversion to little endian.
       *
       * This function checks iterator validity,
       * so can be used when user does not know size of input data.
       *
       * For example:
       * char data[4] = {0x01, 0x02, 0x03, 0x04};
       *
       * uint32_t val = to_little_endian<uint32_t>(data, data + 4);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_little_endian(InputIteratorT first, InputIteratorT last)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;
        unsigned_t val = 0;

        size_t count = 0;

        while (count < sizeof(val))
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert to little endian, iterator is invalid"));
          }

          unsigned_t byteElem = static_cast<uint8_t>(*first);
          val |= (byteElem << (CHAR_BIT * count));

          ++first;
          ++count;
        }

        return val;
      }


      /**
       * Performs conversion to big endian.
       *
       * This function does not check iterator validity,
       * use this only if you sure that iterator remains valid.
       *
       * For example:
       * char data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
       *
       * uint64_t val = to_little_endian<uint64_t>(data);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_big_endian(InputIteratorT input)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;
        unsigned_t val = 0;

        size_t count = sizeof(val);

        while (count > 0)
        {
          unsigned_t byteElem = static_cast<uint8_t>(*input);
          val |= (byteElem << (CHAR_BIT * (count - 1)));

          ++input;
          --count;
        }

        return val;
      }

      /**
       * Performs conversion to big endian.
       *
       * This function does not check iterator validity,
       * so can be used when user does not know size of input data.
       *
       * For example:
       * char data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
       *
       * uint64_t val = to_little_endian<uint64_t>(data, data + 8);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_big_endian(InputIteratorT first, InputIteratorT last)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;
        unsigned_t val = 0;

        size_t count = sizeof(val);

        while (count > 0)
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert to big endian, iterator is invalid"));
          }

          unsigned_t byteElem = static_cast<uint8_t>(*first);
          val |= (byteElem << (CHAR_BIT * (count - 1)));

          ++first;
          --count;
        }

        return val;
      }


      /**
       * This function performs conversion to native endian.
       * On systems with big endian this function is equal to `to_big_endian`,
       * and on system with little endian this function is equal to `to_little_endian`
       *
       * This variant of function does not check iterator validity.
       *
       * For example:
       * char data[2] = {0x01, 0x02};
       *
       * uint16_t val = to_native_endian<uint16_t>(data);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_native_endian(InputIteratorT input)
      {
        IntT val = 0;
        uint8_t * output = static_cast<uint8_t *>(static_cast<void *>(&val));

        size_t count = sizeof(val);

        while (count > 0)
        {
          *output = *input;

          ++input;
          ++output;
          --count;
        }

        return val;
      }


      /**
       * This function performs conversion to native endian.
       * On systems with big endian this function is equal to `to_big_endian`,
       * and on system with little endian this function is equal to `to_little_endian`
       *
       * This variant of function checks iterator validity.
       *
       * For example:
       * char data[2] = {0x01, 0x02};
       *
       * uint16_t val = to_native_endian<uint16_t>(data, data + 2);
       */
      template <typename IntT, typename InputIteratorT>
      IntT to_native_endian(InputIteratorT first, InputIteratorT last)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;

        unsigned_t val = 0;
        uint8_t * output = static_cast<uint8_t *>(static_cast<void *>(&val));

        size_t count = sizeof(val);

        while (count > 0)
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert to native endian, iterator is invalid"));
          }

          *output = *first;

          ++first;
          ++output;
          --count;
        }

        return val;
      }


      /**
       * Convert number to memory as little endian.
       *
       * This function does not check iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_little_endian(x, data); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_little_endian(IntT val, OutputIteratorT begin)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;

        unsigned_t uval = val;
        size_t count = sizeof(uval);

        while (count > 0)
        {
          *begin = static_cast<uint8_t>(uval);
          uval >>= CHAR_BIT;

          ++begin;
          --count;
        }

        return begin;
      }



      /**
       * Convert number to memory as little endian.
       *
       * This function performs checking iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_little_endian(x, data, data + 4); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_little_endian(IntT val, OutputIteratorT first, OutputIteratorT last)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;

        unsigned_t uval = val;
        size_t count = sizeof(uval);

        while (count > 0)
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert from little endian, iterator is out of range"));
          }

          *first = static_cast<uint8_t>(uval);
          uval >>= CHAR_BIT;

          ++first;
          --count;
        }

        return first;
      }


      /**
       * Convert number to memory as big endian.
       *
       * This function does not check iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_big_endian(x, data); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_big_endian(IntT val, OutputIteratorT begin)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;

        unsigned_t uval = val;
        size_t count = sizeof(uval);

        while (count > 0)
        {
          unsigned_t tmp = uval >> (CHAR_BIT * (count - 1));
          *begin = static_cast<uint8_t>(tmp);

          ++begin;
          --count;
        }

        return begin;
      }



      /**
       * Convert number to memory as big endian.
       *
       * This function performs checking iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_big_endian(x, data, data + 4); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_big_endian(IntT val, OutputIteratorT first, OutputIteratorT last)
      {
        typedef typename boost::make_unsigned<IntT>::type unsigned_t;

        unsigned_t uval = val;
        size_t count = sizeof(uval);

        while (count > 0)
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert from big endian, iterator is out of range"));
          }

          unsigned_t tmp = uval >> (CHAR_BIT * (count - 1));
          *first = static_cast<uint8_t>(tmp);

          ++first;
          --count;
        }

        return first;
      }


      /**
       * Convert number to memory as native endian.
       *
       * This function does not check iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_native_endian(x, data); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_native_endian(IntT val, OutputIteratorT begin)
      {
        const uint8_t * input = reinterpret_cast<const uint8_t * >(&val);

        size_t count = sizeof(val);
        while (count > 0)
        {
          *begin = *input;

          ++begin;
          ++input;
          --count;
        }

        return begin;
      }


      /**
       * Convert number to memory as native endian.
       *
       * This function performs checking iterator validity.
       *
       * For example:
       * uint32_t x = 0x12345678;
       *
       * char data[4];
       *
       * char * result = from_native_endian(x, data, data + 4); // actually (result == data + 4)
       *
       */
      template <typename IntT, typename OutputIteratorT>
      OutputIteratorT from_native_endian(IntT val, OutputIteratorT first, OutputIteratorT last)
      {
        const uint8_t * input = reinterpret_cast<const uint8_t * >(&val);

        size_t count = sizeof(val);
        while (count > 0)
        {
          if (first == last)
          {
            BOOST_THROW_EXCEPTION(dio_exception("failed to convert from big endian, iterator is out of range"));
          }

          *first = *input;

          ++first;
          ++input;
          --count;
        }

        return first;
      }

    } // namespace endian

  } // namespace dio

} // namespace boost


#endif /* BOOST_DIO_ENDIAN_HPP */
