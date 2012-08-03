
//  (C) Copyright Alexey Kutumov 2012.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://github.com/prograholic/blog/tree/master/data_io for most recent version.


#ifndef DATA_IO_EXTRACTOR_H
#define DATA_IO_EXTRACTOR_H

#include <stdexcept>

#include "data_io_range.h"


#include "data_io_endian.h"


namespace dio
{

  template <typename InputIteratorT, typename ExtractorT>
  iterator_pair<InputIteratorT> & operator >> (iterator_pair<InputIteratorT> & r, const ExtractorT & extractor)
  {
    r.first = extractor.extract(r.first, r.last);

    return r;
  }

  template <typename PodT, typename ExtractorT>
  iterator_pair<typename std::vector<PodT>::iterator> & operator >> (const std::vector<PodT> & r, const ExtractorT & extractor)
  {
    return (range(r.begin(), r.end()) >> extractor);
  }


#if 0

  namespace detail
  {
    template <typename TagT, typename TypeT>
    struct number_extractor
    {
      TypeT * mX;

      number_extractor(TypeT * x): mX(x)
      {}
    };
  }





  template <typename IntT>
  detail::number_extractor<le_tag, IntT> as(le_tag, IntT * x)
  {
    return detail::number_extractor<le_tag, IntT>(x);
  }

  template <typename IntT>
  detail::number_extractor<be_tag, IntT> as(be_tag, IntT * x)
  {
    return detail::number_extractor<be_tag, IntT>(x);
  }

  template <typename IntT>
  detail::number_extractor<native_tag, IntT> as(native_tag, IntT * x)
  {
    return detail::number_extractor<native_tag, IntT>(x);
  }





  template <typename IntT>
  data_t & operator >> (data_t & data, const detail::number_extractor<le_tag, IntT> & x)
  {
    if (data.size() < sizeof(IntT))
    {
      throw dio_exception("le_extractor: data size too small to get number");
    }
    *(x.mX) = endian::le_mem_2_type<IntT>(data.begin());

    data.erase(data.begin(), data.begin() + sizeof(IntT));

    return data;
  }

#endif //0

}

#endif /* DATA_IO_EXTRACTOR_H */
