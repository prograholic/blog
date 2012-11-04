#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

class application : private boost::noncopyable
{
public:
	application(const std::string & layoutPattern, runnable_factory & factory);

	int run(const std::string & address, const std::string & port);


	static std::string layout(int argc, char * argv []);

private:

	boost::asio::io_service mIo;

	boost::asio::signal_set mSignalSet;

	boost::scoped_ptr<runnable> mRunnable;

	log4cpp::Category & mLogger;



	void stop();

	static log4cpp::Category & initLog(const std::string & layoutPattern);

	void setUpSignals();



	void ioServiceRunWrapper();
};

#endif // APPLICATION_H
