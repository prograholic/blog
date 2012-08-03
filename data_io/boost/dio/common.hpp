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
