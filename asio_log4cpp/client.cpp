#include "client.h"

#include "client_connection.h"



const size_t connectionCount = 1000;


using namespace boost::asio;
using namespace boost::system;
using namespace boost::posix_time;

client::client(boost::asio::io_service & io)
	: mIo(io),
	  mResolver(io),
	  mLogger(log4cpp::Category::getInstance("client")),
	  mConnectionManager(boost::make_shared<connection_manager>())
{
	mLogger.infoStream() << "constructed";
}

void client::run(const std::string & address, const std::string & port)
{
	ip::tcp::resolver::query query(address, port);

	mLogger.infoStream() << "starting asynchronous resolver...";

	mResolver.async_resolve(query,
						   boost::bind(&client::onResolve,
									   this,
									   placeholders::error,
									   placeholders::iterator));
}


void client::stop()
{
	mConnectionManager->stop();
}


void client::startConnect(const ip::tcp::endpoint & ep)
{
	socket_ptr connection = boost::make_shared<ip::tcp::socket>(mIo);

	connection->async_connect(ep,
							  boost::bind(&client::onConnect,
										  this,
										  placeholders::error,
										  connection));
}



///////////////////// on* functions (async handlers) /////////////////////



void client::onResolve(const error_code & ec, ip::tcp::resolver::iterator iterator)
{
	mLogger.infoStream() << "resolving status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		for (size_t i = 0; i != connectionCount; ++i)
		{
			startConnect(iterator->endpoint());
		}
	}
}


void client::onConnect(const error_code & ec, socket_ptr client)
{
	mLogger.infoStream() << "connection status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		mConnectionManager->start_and_add<client_connection>(client);
	}
}
