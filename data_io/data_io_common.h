#ifndef DATA_IO_COMMON_H
#define DATA_IO_COMMON_H

#include <vector>

#include <boost/cstdint.hpp>


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

	typedef std::vector<uint8_t> byte_vector_t;
	typedef byte_vector_t container_t;
	typedef container_t data_t;



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

}


#endif /* DATA_IO_COMMON_H */
