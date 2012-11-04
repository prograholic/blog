#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

class application : private boost::noncopyable
{
public:
	application(runnable_factory & factory);

	int run(const std::string & address, const std::string & port);

private:

	boost::asio::io_service mIo;

	boost::asio::signal_set mSignalSet;

	boost::scoped_ptr<runnable> mRunnable;

	log4cpp::Category & mLogger;



	void stop();

	static log4cpp::Category & initLog();

	void setUpSignals();



	void ioServiceRunWrapper();
};

#endif // APPLICATION_H
