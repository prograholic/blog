#include "MessageDispatcher.h"

#include <stdexcept>


using namespace sample::proto;

MessageDispatcher::MessageDispatcher()
{
}



void MessageDispatcher::addProcessor(MessageProcessorBasePtr processor)
{
	mImpl[processor->id()] = processor;
}



Message MessageDispatcher::dispatch(const Message & query)
{
	DispatcherImplType::iterator it = mImpl.find(query.id());

	if (it == mImpl.end())
	{
		throw std::runtime_error("unknown message id: " + query.id());
	}

	return it->second->process(query);
}

const MessageDispatcher::DispatcherImplType & MessageDispatcher::impl() const
{
	return mImpl;
}
