#ifndef DATA_IO_ENDIAN_H
#define DATA_IO_ENDIAN_H

#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/make_signed.hpp>


#include "data_io_common.h"

namespace dio
{
	namespace endian
	{
		template <typename IntT, typename InputIteratorT>
		IntT le_mem_2_type(InputIteratorT input)
		{
			typedef typename boost::make_unsigned<IntT>::type unsigned_t;
			unsigned_t val = 0;

			size_t count = 0;

			while (count < sizeof(val))
			{
				unsigned_t byteElem = static_cast<uint8_t>(*input);
				val |= (byteElem << (CHAR_BIT * count));

				++input;
				++count;
			}

			return val;
		}

		template <typename IntT, typename InputIteratorT>
		IntT be_mem_2_type(InputIteratorT input)
		{
			typedef typename boost::make_unsigned<IntT>::type unsigned_t;
			unsigned_t val = 0;

			size_t count = sizeof(val);

			while (count > 0)
			{
				unsigned_t byteElem = static_cast<uint8_t>(*input);
				val |= (byteElem << (CHAR_BIT * (count - 1)));

				++input;
				--count;
			}

			return val;
		}

		template <typename IntT, typename InputIteratorT>
		IntT native_mem_2_type(InputIteratorT input)
		{
			IntT val = 0;
			uint8_t * output = reinterpret_cast<uint8_t *>(&val);

			size_t count = sizeof(val);

			while (count > 0)
			{
				*output = *input;

				++input;
				++output;
				--count;
			}

			return val;
		}



		template <typename IntT, typename OutputIteratorT>
		OutputIteratorT le_type_2_mem(IntT val, OutputIteratorT begin)
		{
			OutputIteratorT ptr = begin;
			typedef typename boost::make_unsigned<IntT>::type unsigned_t;

			unsigned_t uval = val;

			size_t count = sizeof(uval);

			while (count > 0)
			{
				*ptr = static_cast<uint8_t>(uval);
				uval >>= CHAR_BIT;

				++ptr;
				--count;
			}

			return begin;
		}


		template <typename IntT, typename OutputIteratorT>
		OutputIteratorT be_type_2_mem(IntT val, OutputIteratorT begin)
		{
			OutputIteratorT ptr = begin;
			typedef typename boost::make_unsigned<IntT>::type unsigned_t;

			unsigned_t uval = val;

			size_t count = sizeof(uval);

			while (count > 0)
			{
				unsigned_t tmp = uval >> (CHAR_BIT * (count - 1));
				*ptr = static_cast<uint8_t>(tmp);

				++ptr;
				--count;
			}

			return begin;
		}


		template <typename IntT, typename OutputIteratorT>
		OutputIteratorT native_type_2_mem(IntT val, OutputIteratorT begin)
		{
			OutputIteratorT ptr = begin;
			const uint8_t * input = reinterpret_cast<const uint8_t * >(&val);

			size_t count = sizeof(val);

			while (count > 0)
			{
				*ptr = *input;

				++ptr;
				++input;
				--count;
			}

			return begin;
		}

	}
}


#endif /* DATA_IO_ENDIAN_H */
