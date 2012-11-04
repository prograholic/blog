#include "application.h"

#include <memory>
#include <stdexcept>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>


using namespace boost::asio;

application::application(const std::string & layoutPattern, runnable_factory & factory)
	: mIo(),
	  mSignalSet(mIo),
	  mLogger(application::initLog(layoutPattern)),
	  mRunnable(factory.create(mIo))
{
	setUpSignals();
}



std::string application::layout(int argc, char * argv [])
{
	std::string usageString = std::string("usage: ") + argv[0] + " <layout>\n"
							  "  <layout> - one of {simple,ndc}";
	if (argc < 2)
	{
		throw std::runtime_error(usageString);
	}

	if (argv[1] == std::string("simple"))
	{
		return consts::simpleLayoutPattern;
	}
	if (argv[1] == std::string("ndc"))
	{
		return consts::ndcLayoutPattern;
	}

	throw std::runtime_error(usageString);
}



int application::run(const std::string & address, const std::string & port)
{
	mLogger.infoStream() << "application starting...";

	mIo.reset();
	boost::thread workerThread(boost::bind(&application::ioServiceRunWrapper, this));

	mRunnable->run(address, port);

	workerThread.join();

	return 0;
}


void application::stop()
{
	mLogger.infoStream() << "application received stop signal...";
	mIo.stop();
	mRunnable->stop();
}


log4cpp::Category & application::initLog(const std::string & layoutPattern)
{
	log4cpp::Category & root = log4cpp::Category::getRoot();

	std::auto_ptr<log4cpp::OstreamAppender> appender(new log4cpp::OstreamAppender("std::cout", &std::cout));
	std::auto_ptr<log4cpp::PatternLayout> layout(new log4cpp::PatternLayout);

	layout->setConversionPattern(layoutPattern);

	appender->setLayout(layout.release());

	root.addAppender(appender.release());
	root.setPriority(log4cpp::Priority::DEBUG);

	root.infoStream() << "starting";

	return root;
}


void application::setUpSignals()
{
	mSignalSet.add(SIGINT);
	mSignalSet.add(SIGQUIT);
	mSignalSet.add(SIGTERM);

	mSignalSet.async_wait(
				boost::bind(&application::stop, this));
}


void application::ioServiceRunWrapper()
{
	io_service::work worker(mIo);

	mIo.run();
}
