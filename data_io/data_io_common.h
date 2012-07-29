#ifndef DATA_IO_COMMON_H
#define DATA_IO_COMMON_H

#include <vector>

#include <boost/cstdint.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/make_signed.hpp>



namespace dio
{
	using boost::int8_t;
	using boost::uint8_t;

	using boost::int16_t;
	using boost::uint16_t;

	using boost::int32_t;
	using boost::uint32_t;

	using boost::int64_t;
	using boost::uint64_t;

	using boost::make_unsigned;
	using boost::make_signed;

	typedef std::vector<uint8_t> byte_vector_t;
	typedef byte_vector_t container_t;
	typedef container_t data_t;

}


#endif /* DATA_IO_COMMON_H */
