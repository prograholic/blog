#ifndef CLIENT_H
#define CLIENT_H

#include "runnable.h"

#include "common.h"

#include "connection_manager.h"

class client : public runnable
{
public:
	client(boost::asio::io_service & io);

	virtual void run(const std::string & address, const std::string & port);

	virtual void stop();


private:

	boost::asio::io_service & mIo;

	boost::asio::ip::tcp::resolver mResolver;

	log4cpp::Category & mLogger;

	connection_manager_ptr mConnectionManager;



	void startResolve();

	void startConnect(const boost::asio::ip::tcp::endpoint & ep);


	/////////

	void onResolve(const boost::system::error_code & ec,
				   boost::asio::ip::tcp::resolver::iterator iterator);


	void onConnect(const boost::system::error_code & ec, socket_ptr client);
};

#endif // CLIENT_H
