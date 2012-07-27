#ifndef DATA_IO_ENDIAN_H
#define DATA_IO_ENDIAN_H

#include "data_io_common.h"

namespace dio
{
	namespace endian
	{
		template <typename IntT, typename InputIteratorT>
		IntT le_mem_2_type(InputIteratorT input)
		{
			typename make_unsigned<IntT>::type val = 0;

			size_t count = sizeof(val);

			while (count > 0)
			{
				val |= static_cast<uint8_t>(*input);

				val <<= CHAR_BIT;

				++input;
				--count;
			}

			return val;
		}

		template <typename IntT, typename InputIteratorT>
		IntT be_mem_2_type(InputIteratorT input)
		{
			typedef typename make_unsigned<IntT>::type unsigned_t;
			unsigned_t val = 0;

			size_t count = sizeof(val);

			while (count > 0)
			{
				unsigned_t byteElem = static_cast<uint8_t>(*input);
				val |= (byteElem << CHAR_BIT * (count - 1));

				++input;
				--count;
			}

			return val;
		}

		template <typename IntT, typename OutputIteratorT>
		OutputIteratorT le_type_2_mem(IntT val, OutputIteratorT begin)
		{
			OutputIteratorT ptr = begin;
			typedef typename make_unsigned<IntT>::type unsigned_t;

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
			typedef typename make_unsigned<IntT>::type unsigned_t;

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

	}
}


#endif /* DATA_IO_ENDIAN_H */
