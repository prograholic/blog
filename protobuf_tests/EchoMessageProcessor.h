#ifndef ECHOMESSAGEPROCESSOR_H
#define ECHOMESSAGEPROCESSOR_H

#include "Echo.pb.h"

#include "MessageDispatcher.h"


class EchoMessageProcessor
		: public ProtoMessageProcessor<sample::proto::EchoQuery, sample::proto::EchoAnswer>
{
public:
	EchoMessageProcessor();

	virtual std::string id() const;


private:

	virtual sample::proto::EchoAnswer doProcessing(const sample::proto::EchoQuery & query);
};

#endif // ECHOMESSAGEPROCESSOR_H
