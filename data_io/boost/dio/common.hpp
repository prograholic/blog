
//  (C) Copyright Alexey Kutumov 2012.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://github.com/prograholic/blog/tree/master/data_io for most recent version.


#ifndef BOOST_DIO_COMMON_HPP
#define BOOST_DIO_COMMON_HPP

#include <stdexcept>

#include <boost/cstdint.hpp>


namespace boost {

  namespace dio {

    enum little_endian_tag
    {
      le
    };

    enum big_endian_tag
    {
      be
    };

    enum native_endian_tag
    {
      ne
    };

    class dio_exception: public std::runtime_error
    {
    public:
      dio_exception(const std::string & what): std::runtime_error(what)
      {}
    };

  } // namespace dio

} // namespace boost

#endif /* BOOST_DIO_COMMON_HPP */
