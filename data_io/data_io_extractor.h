#ifndef DATA_IO_EXTRACTOR_H
#define DATA_IO_EXTRACTOR_H

#include <stdexcept>

#include "data_io_endian.h"


namespace dio
{
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


	class dio_exception: public std::runtime_error
	{
	public:
		dio_exception(const std::string & what): std::runtime_error(what)
		{}
	};


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

}

#endif /* DATA_IO_EXTRACTOR_H */
