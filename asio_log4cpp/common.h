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
#include <log4cpp/NDC.hh>

#include "runnable.h"


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


typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;


inline boost::asio::mutable_buffers_1 to_asio_buffer(message & msg)
{
	BOOST_ASSERT(msg.count <= msg.storage.size());

	return boost::asio::buffer(&msg.storage[msg.count], msg.storage.size() - msg.count);
}





template <typename HandlerT>
class NdcDecorator
{
public:

	explicit NdcDecorator(HandlerT handler, const std::string & ndc)
	: mHandler(handler),
	  mNdc(ndc)
	{

	}


	void operator()()
	{
		mHandler();
	}

	template <typename Arg1>
	void operator() (Arg1 arg1)
	{
		mHandler(arg1);
	}

	template <typename Arg1, typename Arg2>
	void operator() (Arg1 arg1, Arg2 arg2)
	{
		mHandler(arg1, arg2);
	}


	const std::string & ndc() const
	{
		return mNdc;
	}


private:

	HandlerT mHandler;
	std::string mNdc;
};


struct NdcHolder : private boost::noncopyable
{
	NdcHolder(const std::string & ndc)
	{
		log4cpp::NDC::push(ndc);
	}

	~NdcHolder()
	{
		log4cpp::NDC::pop();
	}

};



template <typename HandlerT>
NdcDecorator<HandlerT> decorate(HandlerT handler, const std::string & ndc = log4cpp::NDC::get())
{
	return NdcDecorator<HandlerT>(handler, ndc);
}




template <typename FunctionT, typename HandlerT>
void asio_handler_invoke(FunctionT func, NdcDecorator<HandlerT> * ndcHandler)
{



	NdcHolder ndcHolder(ndcHandler->ndc());

	func();
}







#endif // COMMON_H
