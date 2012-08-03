#ifndef BOOST_DIO_VECTOR_INSERTER_HPP
#define BOOST_DIO_VECTOR_INSERTER_HPP

#include <vector>

#include <boost/dio/inserter_common.hpp>

namespace boost {
  namespace dio {


    /**
     * Simply add value to the end of vector.
     * Function returns reference to holder, so it can be called any times you need:
     *
     * std::vector<uint8_t> holder;
     * holder << 1 << 2 << 3 << 4;
     * BOOST_ASSERT(4, holder.size());
     */
    template <typename PodT, typename IntT>
    std::vector<PodT> & operator <<(std::vector<PodT> & holder, IntT value)
    {
      holder.push_back(value);

      return holder;
    }

  } // namespace dio

} // namespace boost


#endif /* BOOST_DIO_VECTOR_INSERTER_HPP */
