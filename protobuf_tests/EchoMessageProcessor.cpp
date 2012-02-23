#include "EchoMessageProcessor.h"


using namespace sample::proto;

EchoMessageProcessor::EchoMessageProcessor()
{
}


std::string EchoMessageProcessor::id() const
{
	return "Echo";
}


EchoAnswer EchoMessageProcessor::doProcessing(const EchoQuery & query)
{
	EchoAnswer ans;
	ans.set_echo(query.msg());

	return ans;
}
