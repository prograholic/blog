#ifndef DATA_IO_SLICE_H
#define DATA_IO_SLICE_H

#include <boost/assert.hpp>

#include "data_io_common.h"


namespace dio
{

	struct fit_to_data_adapter
	{
		static size_t recalc_first(size_t dataLen, size_t start)
		{
			return (start > dataLen) ? dataLen : start;
		}


		static size_t recalc_last(size_t dataLen, size_t start, size_t count)
		{
			size_t last = start + count;

			return (last > dataLen) ? dataLen : last;
		}
	};



	struct simple_data_adapter
	{
		static size_t recalc_first(size_t dataLen, size_t start)
		{
			BOOST_ASSERT(start <= dataLen);
			return start;
		}


		static size_t recalc_last(size_t dataLen, size_t start, size_t count)
		{
			BOOST_ASSERT(start <= dataLen);

			size_t last = start + count;
			BOOST_ASSERT(last <= dataLen);

			return last;
		}
	};



	template <typename ContainerT, typename SliceAdapterT = simple_data_adapter>
	class out_slice
	{
	public:

		out_slice(const ContainerT & data, size_t start, size_t count)
			: mData(&data), mStart(start), mCount(count)
		{
			BOOST_ASSERT((start + count) >= start); /// prevent wrap around
			BOOST_ASSERT((start + count) >= count); /// prevent wrap around
		}



		typedef typename ContainerT::const_iterator const_iterator;
		typedef typename ContainerT::iterator iterator;

		const_iterator begin() const
		{
			BOOST_ASSERT(mData);

			size_t first = SliceAdapterT::recalc_first(mData->size(), mStart);

			BOOST_ASSERT(first <= mData->size());

			return mData->begin() + first;
		}

		iterator begin()
		{
			BOOST_ASSERT(mData);

			size_t first = SliceAdapterT::recalc_first(mData->size(), mStart);

			BOOST_ASSERT(first <= mData->size());

			return mData->begin() + first;
		}


		const_iterator end() const
		{
			BOOST_ASSERT(mData);

			size_t last = SliceAdapterT::recalc_last(mData->size(), mStart, mCount);

			BOOST_ASSERT(last <= mData->size());

			return mData->begin() + last;
		}

		iterator end()
		{
			BOOST_ASSERT(mData);

			size_t last = SliceAdapterT::recalc_last(mData->size(), mStart, mCount);

			BOOST_ASSERT(last <= mData->size());

			return mData->begin() + last;
		}

		size_t size() const
		{
			return mCount;
		}


	private:
		const ContainerT * mData;

		size_t mStart;
		size_t mCount;
	};


	template <typename ContainerT>
	out_slice<ContainerT> make_out_slice(ContainerT & container, size_t start, size_t count)
	{
		return out_slice<ContainerT>(container, start, count);
	}

	template <typename SliceAdapterT, typename ContainerT>
	out_slice<ContainerT, SliceAdapterT> make_out_slice(ContainerT & container, size_t start, size_t count)
	{
		return out_slice<ContainerT, SliceAdapterT>(container, start, count);
	}

}


#endif /* DATA_IO_SLICE_H */
