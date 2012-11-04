#ifndef SERVER_H
#define SERVER_H

#include "common.h"

#include "connection_manager.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class server : public runnable
{
public:
	server(boost::asio::io_service & io);

	virtual void run(const std::string & address, const std::string & port);

	virtual void stop();

private:

	boost::asio::io_service & mIo;

	boost::asio::ip::tcp::resolver mResolver;

	boost::asio::ip::tcp::acceptor mAcceptor;

	log4cpp::Category & mLogger;


	boost::random::mt19937 mRandomGenerator;
	boost::random::uniform_int_distribution<> mDistribution;


	connection_manager_ptr mConnectionManager;

	void startAccept();




	/////////

	void onResolve(const boost::system::error_code & ec,
				   boost::asio::ip::tcp::resolver::iterator iterator);

	void onAccept(const boost::system::error_code & ec, socket_ptr client);
};


#endif // SERVER_H
