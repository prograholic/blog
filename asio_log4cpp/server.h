#ifndef SERVER_H
#define SERVER_H

#include "common.h"


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class server : private boost::noncopyable
{
public:
	server(boost::asio::io_service & io);

	void run(const std::string & address, const std::string & port);

	void stop();

private:

	boost::asio::io_service & mIo;

	boost::asio::ip::tcp::resolver mResolver;

	boost::asio::ip::tcp::acceptor mAcceptor;

	boost::asio::deadline_timer mTimer;

	log4cpp::Category & mLogger;


	boost::random::mt19937 mRandomGenerator;
	boost::random::uniform_int_distribution<> mDistribution;


	void startAccept();

	void startReading(socket_ptr client, message_ptr msg);

	void startWriting(socket_ptr client, message_ptr msg);

	void startWaiting(socket_ptr client, const boost::posix_time::time_duration & timeout);


	/////////

	void onResolve(const boost::system::error_code & ec,
				   boost::asio::ip::tcp::resolver::iterator iterator);

	void onAccept(const boost::system::error_code & ec, socket_ptr client);

	void onWrite(const boost::system::error_code & ec, size_t bytes_transferred, socket_ptr client, message_ptr msg);

	void onWait(const boost::system::error_code & ec, socket_ptr client);

	void onRead(const boost::system::error_code & ec, size_t bytes_transferred, socket_ptr client, message_ptr msg);
};

#endif // SERVER_H
