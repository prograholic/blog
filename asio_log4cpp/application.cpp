#include "application.h"

#include <memory>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>


using namespace boost::asio;

application::application()
	: mIo(),
	  mSignalSet(mIo),
	  mServer(mIo),
	  mLogger(application::initLog())
{
	setUpSignals();
}


int application::run()
{
	mLogger.infoStream() << "application starting...";

	mIo.reset();
	boost::thread workerThread(boost::bind(&application::ioServiceRunWrapper, this));

	mServer.run("0.0.0.0", "12345");

	workerThread.join();

	return 0;
}


void application::stop()
{
	mLogger.infoStream() << "application received stop signal...";
	mIo.stop();
	mServer.stop();
}


log4cpp::Category & application::initLog()
{
	log4cpp::Category & root = log4cpp::Category::getRoot();

	std::auto_ptr<log4cpp::OstreamAppender> appender(new log4cpp::OstreamAppender("std::cout", &std::cout));
	std::auto_ptr<log4cpp::PatternLayout> layout(new log4cpp::PatternLayout);

	layout->setConversionPattern("%p %m %x%n");

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
