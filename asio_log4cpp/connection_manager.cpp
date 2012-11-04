#include "connection_manager.h"

#include <boost/foreach.hpp>

connection_manager::connection_manager()
	: mConnectionPool(),
	  mPoolMutex()
{
}


void connection_manager::put(connection_base_ptr connection)
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	mConnectionPool.insert(connection);
}


void connection_manager::release(connection_base_ptr connection)
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	mConnectionPool.erase(connection);
}


void connection_manager::stop()
{
	boost::mutex::scoped_lock lockGuard(mPoolMutex);

	BOOST_FOREACH(connection_base_weak_ptr weakConnection, mConnectionPool)
	{
		if (connection_base_ptr connection = weakConnection.lock())
		{
			connection->stop();
		}
	}
}
