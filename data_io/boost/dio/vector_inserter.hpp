
//  (C) Copyright Alexey Kutumov 2012.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://github.com/prograholic/blog/tree/master/data_io for most recent version.

#ifndef BOOST_DIO_VECTOR_INSERTER_HPP
#define BOOST_DIO_VECTOR_INSERTER_HPP

#include <vector>

#include <boost/array.hpp>

#include <boost/dio/inserter_common.hpp>

namespace boost {
  namespace dio {

    /**
     * Simply add value to the end of vector.
     * Function returns reference to holder, so it can be called any times and mixed with other inserters:
     *
     * std::vector<uint8_t> holder;
     * holder << 1 << 2 << 3 << 4;
     * BOOST_ASSERT(4, holder.size());
     */
    template <typename HolderT, typename ValueT>
    std::vector<HolderT> & operator <<(std::vector<HolderT> & holder, ValueT value)
    {
      holder.push_back(value);

      return holder;
    }


    /**
     * Add value to vector according to given tag.
     * Function returns reference to holder, so it can be called many times and mixed with other inserters:
     *
     * std::vector<uint8_t> holder;
     * holder << as<uint16_t>(le, 0x1234) << as<uint16_t>(be, 0x5678);
     * BOOST_ASSERT(4, holder.size());
     */
    template <typename HolderT, typename TagT, typename IntT>
    std::vector<HolderT> & operator << (
        std::vector<HolderT> & holder,
        const detail::inserter<TagT, IntT> & ins)
    {
      ins.insert(std::back_inserter(holder));

      return holder;
    }

    /**
     * Concatenate two vectors and store result in holder;
     * Function returns reference to holder, so it can be called many times and mixed with other inserters:
     *
     * std::vector<uint8_t> holder;
     * std::vector<int8_t> input;
     * input.push_back(1);
     *
     * holder << input;
     * BOOST_ASSERT(input.size() == holder.size());
     */
    template <typename HolderT, typename InputT>
    std::vector<HolderT> & operator << (
        std::vector<HolderT> & holder,
        const std::vector<InputT> & input)
    {
      holder.insert(holder.end(), input.begin(), input.end());

      return holder;
    }


    /**
     * @brief Adds array to the end of the vector
     *
     * Function returns reference to holder, so it can be called many times and mixed with other inserters:
     *
     * std::vector<uint8_t> holder;
     * char data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
     *
     * holder << data;
     * BOOST_ASSERT(8, holder.size());
     */
    template <typename HolderT, typename InputT, size_t N>
    std::vector<HolderT> & operator << (
        std::vector<HolderT> & holder,
        const InputT (& input) [N])
    {
      holder.insert(holder.end(), input, input + N);

      return holder;
    }


    /**
     * @brief Adds boost::array to the end of holder
     *
     * Function returns reference to holder, so it can be called many times and mixed with other inserters:
     *
     * std::vector<uint8_t> holder;
     * boost::array<int8_t, 8> data = {{0, 1, 2, 3, 4, 5, 6, 7}};
     *
     * holder << data;
     * BOOST_ASSERT(8, holder.size());
     */
    template <typename HolderT, typename InputT, size_t N>
    std::vector<HolderT> & operator << (
        std::vector<HolderT> & holder,
        const ::boost::array<InputT, N> & input)
    {
      holder.insert(holder.end(), input.begin(), input.end());

      return holder;
    }


  } // namespace dio

} // namespace boost


#endif /* BOOST_DIO_VECTOR_INSERTER_HPP */
