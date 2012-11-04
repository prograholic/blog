#include "server.h"

#include <ctime>

#include "server_connection.h"

using namespace boost::asio;
using namespace boost::system;
using namespace boost::posix_time;



server::server(boost::asio::io_service & io)
	: mIo(io),
	  mResolver(io),
	  mAcceptor(io),
	  mLogger(log4cpp::Category::getInstance("server")),
	  mRandomGenerator(::time(0)),
	  mDistribution(consts::lowerBound, consts::upperBound),
	  mConnectionManager(boost::make_shared<connection_manager>())
{
	mLogger.infoStream() << "constructed";
}




void server::run(const std::string & address, const std::string & port)
{
	ip::tcp::resolver::query query(address, port);

	mLogger.infoStream() << "starting asynchronous resolver...";

	mResolver.async_resolve(query,
						   boost::bind(&server::onResolve,
									   this,
									   placeholders::error,
									   placeholders::iterator));
}

void server::stop()
{
	mResolver.cancel();
	mAcceptor.cancel();

	mConnectionManager->stop();
}





///////////////////// on* functions (async handlers) /////////////////////

void server::startAccept()
{
	mLogger.infoStream() << "starting asynchronous accept...";

	socket_ptr client = boost::make_shared<ip::tcp::socket>(boost::ref(mIo));

	mAcceptor.async_accept(*client,
						   boost::bind(&server::onAccept,
									   this,
									   placeholders::error,
									   client));
}





/////// on* functions (async handlers) ///////


void server::onResolve(const error_code & ec, ip::tcp::resolver::iterator iterator)
{
	mLogger.infoStream() << "resolving status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		mAcceptor.open(ip::tcp::v4());

		socket_base::reuse_address reuse_address(true);
		mAcceptor.set_option(reuse_address);

		mAcceptor.bind(*iterator);
		mAcceptor.listen();
		startAccept();
	}
}



void server::onAccept(const error_code & ec, socket_ptr client)
{
	mLogger.infoStream() << "accept status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		size_t timeout = mDistribution(mRandomGenerator);
		mLogger.infoStream() << "timeout generated: " << timeout;

		mConnectionManager->start_and_add<server_connection>(client, timeout);

		startAccept();
	}
}


