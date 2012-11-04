#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <boost/noncopyable.hpp>
#include <boost/asio/io_service.hpp>

class runnable : private boost::noncopyable
{
public:

	virtual ~runnable()
	{
	}

	virtual void run(const std::string & address, const std::string & port) = 0;

	virtual void stop() = 0;
};



class runnable_factory : private boost::noncopyable
{
public:

	/// @note ownership transfers to caller
	virtual runnable * create(boost::asio::io_service & io) = 0;
};




template <typename RunnableT>
class template_runnable_factory : public runnable_factory
{
public:

	virtual RunnableT * create(boost::asio::io_service & io)
	{
		return new RunnableT(io);
	}
};

#endif // RUNNABLE_H
