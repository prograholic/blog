#ifndef DATA_IO_INSERTER_H
#define DATA_IO_INSERTER_H

#include "data_io_endian.h"


namespace dio
{
	namespace detail
	{
		template <typename TagT, typename TypeT>
		struct number_inserter
		{
			TypeT mX;

			number_inserter(TypeT x): mX(x)
			{}

		};
	}

	enum le_tag
	{
		le
	};

	enum be_tag
	{
		be
	};


	template <typename IntT>
	detail::number_inserter<le_tag, IntT> insert(le_tag, IntT x)
	{
		return detail::number_inserter<le_tag, IntT>(x);
	}

	template <typename IntT>
	detail::number_inserter<be_tag, IntT> insert(be_tag, IntT x)
	{
		return detail::number_inserter<be_tag, IntT>(x);
	}


	template <typename TypeT>
	data_t & operator << (data_t & data, const detail::number_inserter<le_tag, TypeT> & inserter)
	{
		endian::le_type_2_mem(inserter.mX, std::back_inserter(data));

		return data;
	}

	template <typename TypeT>
	data_t & operator << (data_t & data, const detail::number_inserter<be_tag, TypeT> & inserter)
	{
		endian::be_type_2_mem(inserter.mX, std::back_inserter(data));

		return data;
	}



}



#endif /* DATA_IO_INSERTER_H */
