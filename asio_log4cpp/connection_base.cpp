#include "connection_base.h"

#include "connection_manager.h"

connection_base::connection_base(connection_manager_ptr connectionManager)
	: mConnectionManager(connectionManager)
{

}



connection_base::~connection_base()
{
	if (connection_manager_ptr connectionManager = mConnectionManager.lock())
	{
		connectionManager->release(this);
	}
}



void connection_base::start(const std::string & ndc)
{
	NdcHolder ndcHolder(ndc);

	doStart(ndc);
}
