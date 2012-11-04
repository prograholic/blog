#include "connection_manager.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

connection_manager::connection_manager()
	: mConnectionPool(),
	  mPoolMutex(),
	  mCount(0)
{
}


void connection_manager::put(connection_base_ptr connection)
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	mConnectionPool[connection.get()] = connection;
}


void connection_manager::release(connection_base * connection)
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	mConnectionPool.erase(connection);
}


void connection_manager::stop()
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	BOOST_FOREACH(connection_pool_t::value_type & weakConnection, mConnectionPool)
	{
		if (connection_base_ptr connection = weakConnection.second.lock())
		{
			connection->stop();
		}
	}
}



std::string connection_manager::nextCounter()
{
	long val = static_cast<long>(++mCount);

	return boost::lexical_cast<std::string>(val);
}
