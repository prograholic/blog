#ifndef SERVERSTATUSMESSAGEPROCESSOR_H
#define SERVERSTATUSMESSAGEPROCESSOR_H

#include "MessageDispatcher.h"

#include "ServerStatus.pb.h"


class ServerStatusMessageProcessor:
		public ProtoMessageProcessor<sample::proto::ServerStatusQuery,
			sample::proto::ServerStatusAnswer>
{
public:

	typedef sample::proto::ServerStatusQuery query_type;
	typedef sample::proto::ServerStatusAnswer answer_type;

	ServerStatusMessageProcessor(MessageDispatcher * dispatcher);

	virtual std::string id() const;


private:

	virtual answer_type doProcessing(const query_type & query);


	MessageDispatcher * mDispatcher;

};

#endif // SERVERSTATUSMESSAGEPROCESSOR_H
