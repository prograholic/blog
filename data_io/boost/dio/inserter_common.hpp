
//  (C) Copyright Alexey Kutumov 2012.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://github.com/prograholic/blog/tree/master/data_io for most recent version.


#ifndef BOOST_DIO_INSERTER_COMMON_HPP
#define BOOST_DIO_INSERTER_COMMON_HPP

#include <boost/dio/endian.hpp>

namespace boost {

  namespace dio {

    namespace detail {

      /**
       * This type allows to insert values in different ways.
       * This struct intentionally incomplete. All work must be done in partial specializations (see below).
       */
      template <typename TypeT, typename TagT>
      struct inserter;


      /**
       * This is partial specialization for insert data as big endian.
       *
       * This struct has two methods `insert` - safe and unsafe.
       * Safe method checks iterator validity (calls safe version of `from_little_endian` function)
       * Unsafe method does not checks iterator.
       */
      template <typename TypeT>
      struct inserter<TypeT, little_endian_tag>
      {
        TypeT mX;

        inserter(TypeT x): mX(x)
        {}

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT first, OutputIteratorT last) const
        {
          return endian::from_little_endian(mX, first, last);
        }

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT begin) const
        {
          return endian::from_little_endian(mX, begin);
        }
      };


      /**
       * This is partial specialization for insert data as big endian
       *
       * @sa Description of methods in specialisation for little endian
       */
      template <typename TypeT>
      struct inserter<TypeT, big_endian_tag>
      {
        TypeT mX;

        inserter(TypeT x): mX(x)
        {}

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT first, OutputIteratorT last) const
        {
          return endian::from_big_endian(mX, first, last);
        }

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT begin) const
        {
          return endian::from_big_endian(mX, begin);
        }
      };


      /**
       * This is partial specialization for insert data as native endian
       *
       * @sa Description of methods in specialisation for little endian
       */
      template <typename TypeT>
      struct inserter<TypeT, native_endian_tag>
      {
        TypeT mX;

        inserter(TypeT x): mX(x)
        {}

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT first, OutputIteratorT last) const
        {
          return endian::from_native_endian(mX, first, last);
        }

        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT begin) const
        {
          return endian::from_native_endian(mX, begin);
        }
      };




      struct range_tag {};

      template <typename InputIteratorT>
      struct inserter<InputIteratorT, range_tag>
      {
        InputIteratorT mFirst;
        InputIteratorT mLast;

        inserter(InputIteratorT first, InputIteratorT last)
          : mFirst(first), mLast(last)
        {}


        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT input) const
        {
          for (InputIteratorT it = mFirst; it != mLast; ++it, ++input)
          {
            *input = *it;
          }

          return input;
        }


        template <typename OutputIteratorT>
        OutputIteratorT insert(OutputIteratorT first, OutputIteratorT last) const
        {
          for (InputIteratorT it = mFirst; it != mLast; ++it, ++first)
          {
            if (first == last)
            {
              BOOST_THROW_EXCEPTION(dio_exception("Range too big to fit into given iterator range"));
            }
            *first = *it;
          }

          return first;
        }

      };

    } // namespace detail


    /**
     * This function constructs needed inserter (dispatched by given EndianTagT).
     */
    template <typename IntT, typename EndianTagT>
    detail::inserter<IntT, EndianTagT> as(EndianTagT /* tag */, IntT value)
    {
      return detail::inserter<IntT, EndianTagT>(value);
    }


    /**
     * Creates range fom two iterators.
     *
     * This function is helpful, when you need to insert a range between two iterators.
     *
     * @todo See also Boost.Range
     */
    template <typename InputIteratorT>
    detail::inserter<InputIteratorT, detail::range_tag> make_range(InputIteratorT first, InputIteratorT last)
    {
      return detail::inserter<InputIteratorT, detail::range_tag>(first, last);
    }


  } // namespace dio

} // namespace boost


#if 0

namespace dio
{

  template <typename OutputIteratorT, typename InserterT>
  iterator_pair<OutputIteratorT> & operator << (iterator_pair<OutputIteratorT> & r, const InserterT & inserter)
  {
    r.first = inserter.insert(r.first, r.last);

    return r;
  }


  template <typename PodT, typename InserterT>
  std::vector<PodT> & operator << (std::vector<PodT> & r, const InserterT & inserter)
  {
    inserter.insert(std::back_inserter(r), std::back_inserter(r));

    return r;
  }






  template <typename TypeT>
  detail::value_inserter<TypeT> value(TypeT x)
  {
    return detail::value_inserter<TypeT>(x);
  }


  template <typename ContainerT>
  detail::range_inserter<typename ContainerT::const_iterator> whole(const ContainerT & container)
  {
    return range(container.begin(), container.end());
  }


  template <typename ContainerT>
  detail::range_inserter<typename ContainerT::const_iterator>
  slice(const ContainerT & r, size_t offset, size_t size)
  {
    typename ContainerT::const_iterator first = r.begin();
    typename ContainerT::const_iterator last = r.begin();

    std::advance(first, offset);
    std::advance(last, offset + size);

    return range(first, last);
  }





}

#endif //0

#endif /* BOOST_DIO_INSERTER_COMMON_HPP */
