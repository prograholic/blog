#include "MessageDispatcher.h"

#include "ServerStatusMessageProcessor.h"
#include "EchoMessageProcessor.h"

#include <iostream>

#include <boost/smart_ptr/make_shared.hpp>



using namespace sample::proto;


int main()
{
	try
	{
		MessageDispatcher md;

		md.addProcessor(boost::make_shared<ServerStatusMessageProcessor>(&md));
		md.addProcessor(boost::make_shared<EchoMessageProcessor>());


		Message q;
		q.set_id("ServerStatus");
		Message ans = md.dispatch(q);

		std::cout << "query:  " << q.DebugString() << std::endl;
		std::cout << "answer: " << ans.DebugString() << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}






	return 0;
}
