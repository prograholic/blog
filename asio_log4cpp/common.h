#ifndef COMMON_H
#define COMMON_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>


#include <log4cpp/Category.hh>



namespace consts
{
	const char answer [] = "GOODBYE";
	const size_t sizeHint = 1000;

	const int lowerBound = 0;

	const int upperBound = 1000;
}







typedef std::vector<boost::uint8_t> message_t;



struct message
{
	message_t storage;

	size_t count;

	size_t timeout;

	explicit message()
		: storage(consts::sizeHint),
		  count(0),
		  timeout(0)
	{}

	explicit message(size_t t)
		: storage(),
		  count(0),
		  timeout(t)
	{
		std::string msg = boost::lexical_cast<std::string>(t);
		storage.assign(msg.begin(), msg.end());

		/// terminating character
		storage.push_back(0);
	}


	explicit message(const std::string & msg)
		: storage(msg.begin(), msg.end()),
		  count(0),
		  timeout(0)
	{
		/// terminating character
		storage.push_back(0);
	}
};

typedef boost::shared_ptr<message> message_ptr;




typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;


inline boost::asio::mutable_buffers_1 to_asio_buffer(message_ptr msg)
{
	BOOST_ASSERT(msg->count <= msg->storage.size());

	return boost::asio::buffer(&msg->storage[msg->count], msg->storage.size() - msg->count);
}




inline message_ptr to_message(size_t timeout)
{
	message_ptr res = boost::make_shared<message>(timeout);

	return res;
}


inline message_ptr to_message(const std::string & msg)
{
	message_ptr res = boost::make_shared<message>(msg);

	return res;
}






#endif // COMMON_H
