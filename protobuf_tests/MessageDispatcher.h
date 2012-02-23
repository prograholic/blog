#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <map>
#include <stdexcept>

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "message.pb.h"



class MessageProcessingError: public std::runtime_error
{
public:

	MessageProcessingError(const std::string & e): std::runtime_error(e)
	{

	}

};


class MessageProcessorBase: private boost::noncopyable
{
public:

	virtual ~MessageProcessorBase()
	{
	}

	virtual std::string id() const = 0;


	virtual sample::proto::Message process(const sample::proto::Message & query) = 0;

private:

};


template <typename ProtoQueryT, typename ProtoAnswerT>
class ProtoMessageProcessor: public MessageProcessorBase
{
public:

	virtual sample::proto::Message process(const sample::proto::Message & query)
	{
		ProtoQueryT underlyingQuery;
		if (!underlyingQuery.ParseFromString(query.data()))
		{
			throw MessageProcessingError("Failed to parse query: " + query.ShortDebugString());
		}

		ProtoAnswerT underlyingAnswer = doProcessing(underlyingQuery);

		sample::proto::Message a;
		a.set_id(query.id());

		if (!underlyingAnswer.SerializeToString(a.mutable_data()))
		{
			throw MessageProcessingError("Failed to prepare answer: " + underlyingAnswer.ShortDebugString());
		}

		return a;
	}

private:

	virtual ProtoAnswerT doProcessing(const ProtoQueryT & query) = 0;
};




typedef boost::shared_ptr<MessageProcessorBase> MessageProcessorBasePtr;






class MessageDispatcher
{
public:
	MessageDispatcher();


	void addProcessor(MessageProcessorBasePtr processor);

	sample::proto::Message dispatch(const sample::proto::Message & query);

	typedef std::map<std::string, MessageProcessorBasePtr> DispatcherImplType;

	const DispatcherImplType & impl() const;

private:



	DispatcherImplType mImpl;

};

#endif // MESSAGEDISPATCHER_H
