#ifndef DATA_IO_INSERTER_H
#define DATA_IO_INSERTER_H

#include "data_io_endian.h"
#include "data_io_slice.h"


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

	enum native_tag
	{
		native
	};


	template <typename IntT>
	detail::number_inserter<le_tag, IntT> as(le_tag, IntT x)
	{
		return detail::number_inserter<le_tag, IntT>(x);
	}

	template <typename IntT>
	detail::number_inserter<be_tag, IntT> as(be_tag, IntT x)
	{
		return detail::number_inserter<be_tag, IntT>(x);
	}

	template <typename IntT>
	detail::number_inserter<native_tag, IntT> as(native_tag, IntT x)
	{
		return detail::number_inserter<native_tag, IntT>(x);
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

	template <typename TypeT>
	data_t & operator << (data_t & data, const detail::number_inserter<native_tag, TypeT> & inserter)
	{
		endian::native_type_2_mem(inserter.mX, std::back_inserter(data));

		return data;
	}


	data_t & operator << (data_t & data, uint8_t x)
	{
		data.push_back(x);

		return data;
	}


	data_t & operator << (data_t & data, const data_t & x)
	{
		data.insert(data.end(), x.begin(), x.end());
	}


	template <typename ContainerT, typename SliceAdapterT>
	data_t & operator << (data_t & data, const out_slice<ContainerT, SliceAdapterT> & s)
	{
		data.insert(data.end(), s.begin(), s.end());

		return data;
	}



}



#endif /* DATA_IO_INSERTER_H */
