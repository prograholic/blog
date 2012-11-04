#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "connection_base.h"

#include "common.h"

class client_connection : public connection_base
{
public:
	client_connection(connection_manager_ptr connectionManager, socket_ptr connection);

	~client_connection();


	virtual void stop();


private:

	socket_ptr mSocket;

	message mInputMsg;

	message mOutputMsg;

	log4cpp::Category & mLogger;

	boost::asio::deadline_timer mTimer;




	virtual void doStart(const std::string & ndc);


	void startReading(const std::string & ndc);

	void startWaiting(const boost::posix_time::time_duration & timeout);

	void startWriting();


	///////////////////////////////////////


	void onRead(const boost::system::error_code & ec, size_t bytes_transferred);

	void onWait(const boost::system::error_code & ec);

	void onWrite(const boost::system::error_code & ec, size_t bytes_transferred);

};

#endif // CLIENT_CONNECTION_H
