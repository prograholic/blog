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


		template <typename InputIteratorT>
		struct range_inserter
		{
			InputIteratorT first;
			InputIteratorT last;

			range_inserter(InputIteratorT f, InputIteratorT l): first(f), last(l)
			{}
		};
	}

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

	template <typename InputIteratorT>
	detail::range_inserter<InputIteratorT> range(InputIteratorT first, InputIteratorT last)
	{
		return detail::range_inserter<InputIteratorT>(first, last);
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

	template <typename ContainerT, typename SliceAdapterT>
	data_t & operator << (data_t & data, const slice_container<ContainerT, SliceAdapterT> & s)
	{
		data.insert(data.end(), s.begin(), s.end());

		return data;
	}

	template <typename InputIteratorT>
	data_t & operator << (data_t & data, const detail::range_inserter<InputIteratorT> & r)
	{
		data.insert(data.end(), r.first, r.last);

		return data;
	}

}



#endif /* DATA_IO_INSERTER_H */
