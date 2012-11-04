#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <set>

#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include "connection_base.h"



class connection_manager : public boost::enable_shared_from_this<connection_manager>
{
public:
	connection_manager();


	template <typename ConnectionT, typename ... ArgsT>
	void start_and_add(ArgsT ... args)
	{
		boost::shared_ptr<ConnectionT> connection = boost::make_shared<ConnectionT>(shared_from_this(), args ...);

		connection->start();

		put(connection);
	}

	void release(connection_base_ptr connection);

	void stop();

private:

	std::set<connection_base_weak_ptr> mConnectionPool;
	boost::mutex mPoolMutex;

	void put(connection_base_ptr connection);

};

#endif // CONNECTION_MANAGER_H
