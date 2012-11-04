#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <map>

#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>

#include "connection_base.h"



class connection_manager : public boost::enable_shared_from_this<connection_manager>
{
public:
	connection_manager();


	template <typename ConnectionT, typename ... ArgsT>
	void start_and_add(ArgsT ... args)
	{
		boost::shared_ptr<ConnectionT> connection = boost::make_shared<ConnectionT>(shared_from_this(), args ...);

		std::string ndc = "<SID=" + this->nextCounter() + ">";

		connection->start(ndc);

		put(connection);
	}

	void release(connection_base * connection);

	void stop();

	std::string nextCounter();

private:

	typedef std::map<connection_base * , connection_base_weak_ptr> connection_pool_t;
	connection_pool_t mConnectionPool;
	boost::mutex mPoolMutex;


	boost::detail::atomic_count mCount;

	void put(connection_base_ptr connection);

};

#endif // CONNECTION_MANAGER_H
