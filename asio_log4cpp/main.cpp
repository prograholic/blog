#include "server.h"

#include <iostream>
#include <memory>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>





void initLog()
{
	log4cpp::Category & root = log4cpp::Category::getRoot();


	std::auto_ptr<log4cpp::OstreamAppender> appender(new log4cpp::OstreamAppender("std::cout", &std::cout));

	std::auto_ptr<log4cpp::PatternLayout> layout(new log4cpp::PatternLayout);

	layout->setConversionPattern("%p %m %x%n");

	appender->setLayout(layout.release());

	root.addAppender(appender.release());
	root.setPriority(log4cpp::Priority::DEBUG);





	root.infoStream() << "starting";
}

int main()
{
	try
	{
		initLog();

		boost::asio::io_service io;

		return 0;
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "UNKNOWN ERROR" << std::endl;
		return 2;
	}
}
