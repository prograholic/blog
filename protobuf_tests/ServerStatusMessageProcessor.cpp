#include "ServerStatusMessageProcessor.h"

using namespace sample::proto;


ServerStatusMessageProcessor::ServerStatusMessageProcessor(MessageDispatcher * dispatcher)
	: mDispatcher(dispatcher)
{
}



std::string ServerStatusMessageProcessor::id() const
{
	return "ServerStatus";
}


ServerStatusAnswer ServerStatusMessageProcessor::doProcessing(const ServerStatusQuery & query)
{
	ServerStatusAnswer s;


	s.set_threadcount(10);

	typedef MessageDispatcher::DispatcherImplType::const_iterator md_iterator;

	const MessageDispatcher::DispatcherImplType & mdImpl = mDispatcher->impl();

	for (md_iterator it = mdImpl.begin(); it != mdImpl.end(); ++it)
	{
		s.add_listeners(it->first);
	}


	return s;
}
