#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "connection_base.h"

#include "common.h"

class server_connection : public connection_base
{
public:
	server_connection(connection_manager_ptr connectionManager, socket_ptr sock, size_t timeout);

	virtual void start();

	virtual void stop();

private:

	socket_ptr mSocket;

	message mInputMsg;

	message mOutputMsg;

	log4cpp::Category & mLogger;

	boost::asio::deadline_timer mTimer;

	std::string mNdc;


	void startWriting();

	void startWaiting(const boost::posix_time::time_duration & timeout);

	void startReading();


	///////////////////////////////////////



	void onWrite(const boost::system::error_code & ec, size_t bytes_transferred);

	void onWait(const boost::system::error_code & ec);

	void onRead(const boost::system::error_code & ec, size_t bytes_transferred);

};



typedef boost::shared_ptr<server_connection> server_connection_ptr;

#endif // SERVER_CONNECTION_H
