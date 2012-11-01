#include "server.h"

#include <ctime>

using namespace boost::asio;
using namespace boost::system;
using namespace boost::posix_time;



server::server(boost::asio::io_service & io)
	: mIo(io),
	  mResolver(io),
	  mAcceptor(io),
	  mTimer(io),
	  mLogger(log4cpp::Category::getInstance("server")),
	  mRandomGenerator(::time(0)),
	  mDistribution(consts::lowerBound, consts::upperBound)
{
	mLogger.infoStream() << "constructed";
}




void server::run(const std::string & addr, const std::string & port)
{
	ip::tcp::resolver::query query(addr, port);

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
	mTimer.cancel();
}





/////// start* functions (start async ops) ///////

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




void server::startWriting(socket_ptr client, message_ptr msg)
{
	mLogger.infoStream() << "starting asynchronous write...";


	async_write(*client,
				to_asio_buffer(msg),
				boost::bind(&server::onWrite,
							this,
							placeholders::error,
							placeholders::bytes_transferred,
							client,
							msg));
}




void server::startWaiting(socket_ptr client, const time_duration & timeout)
{
	mLogger.infoStream() << "starting asynchronous timeout " << timeout << " ...";


	mTimer.expires_from_now(timeout);
	mTimer.async_wait(
				boost::bind(&server::onWait,
							this,
							placeholders::error,
							client));
}



void server::startReading(socket_ptr client, message_ptr msg)
{
	mLogger.infoStream() << "starting asynchronous read...";

	client->async_read_some(to_asio_buffer(msg),
							boost::bind(&server::onRead,
										this,
										placeholders::error,
										placeholders::bytes_transferred,
										client,
										msg));
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
		startWriting(client, to_message(timeout));
	}
}



void server::onWrite(const error_code & ec, size_t bytes_transferred, socket_ptr client, message_ptr msg)
{
	mLogger.infoStream() << "write status: " << ec << ", "
							"message: " << ec.message() << ", "
							"bytes written: " << bytes_transferred;

	if (!ec)
	{
		startWaiting(client, boost::posix_time::milliseconds(msg->timeout));
	}
}




void server::onWait(const boost::system::error_code & ec, socket_ptr client)
{
	mLogger.infoStream() << "timer status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		message_ptr answer = boost::make_shared<message>();
		startReading(client, answer);
	}
}




void server::onRead(const error_code & ec, size_t bytes_transferred, socket_ptr client, message_ptr msg)
{
	mLogger.infoStream() << "read status: " << ec << ", message: " << ec.message();

	if (!ec)
	{

		/// move current position
		msg->count += bytes_transferred;
		BOOST_ASSERT(msg->count <= msg->storage.size());

		if ((msg->count > 0) && (msg->storage[msg->count - 1] == 0))
		{
			std::string clientAnswer(msg->storage.begin(), msg->storage.begin() + (msg->count - 1));

			mLogger.infoStream() << "answer from client readed: [" << clientAnswer << "]";
		}
		else
		{
			mLogger.infoStream() << "received partial message, waiting end of message...";
			startReading(client, msg);
		}
	}
}
