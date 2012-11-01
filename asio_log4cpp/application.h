#ifndef APPLICATION_H
#define APPLICATION_H

#include "server.h"

class application : private boost::noncopyable
{
public:
	application();

	int run();

private:

	boost::asio::io_service mIo;

	boost::asio::signal_set mSignalSet;

	server mServer;

	log4cpp::Category & mLogger;



	void stop();

	static log4cpp::Category & initLog();

	void setUpSignals();



	void ioServiceRunWrapper();
};

#endif // APPLICATION_H
