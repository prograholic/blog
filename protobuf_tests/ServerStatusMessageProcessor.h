#ifndef SERVERSTATUSMESSAGEPROCESSOR_H
#define SERVERSTATUSMESSAGEPROCESSOR_H

#include "MessageDispatcher.h"

#include "ServerStatus.pb.h"


class ServerStatusMessageProcessor:
		public ProtoMessageProcessor<sample::proto::ServerStatusQuery, sample::proto::ServerStatusAnswer>
{
public:

	ServerStatusMessageProcessor(MessageDispatcher * dispatcher);

	virtual std::string id() const;


private:

	virtual sample::proto::ServerStatusAnswer doProcessing(const sample::proto::ServerStatusQuery & query);


	MessageDispatcher * mDispatcher;

};

#endif // SERVERSTATUSMESSAGEPROCESSOR_H
