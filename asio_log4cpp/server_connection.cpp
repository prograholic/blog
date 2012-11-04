#include "server_connection.h"

#include "connection_manager.h"

using namespace boost::asio;
using namespace boost::system;
using namespace boost::posix_time;

server_connection::server_connection(connection_manager_ptr connectionManager, socket_ptr sock, size_t timeout)
	: connection_base(connectionManager),
	  mSocket(sock),
	  mInputMsg(),
	  mOutputMsg(timeout),
	  mLogger(log4cpp::Category::getInstance("server.connection")),
	  mTimer(sock->get_io_service())
{
}


void server_connection::doStart(const std::string & ndc)
{
	startWriting(ndc);
}

void server_connection::stop()
{
	mSocket->close();
	mTimer.cancel();
}


void server_connection::startWriting(const std::string & ndc)
{
	mLogger.infoStream() << "starting asynchronous write...";

	async_write(*mSocket,
				to_asio_buffer(mOutputMsg),
				decorate(
					boost::bind(&server_connection::onWrite,
								shared_from(this),
								placeholders::error,
								placeholders::bytes_transferred),
					ndc));
}


void server_connection::startWaiting(const time_duration & timeout)
{
	mLogger.infoStream() << "starting asynchronous timeout " << timeout << " ...";

	mTimer.expires_from_now(timeout);
	mTimer.async_wait(
				decorate(
					boost::bind(&server_connection::onWait,
								shared_from(this),
								placeholders::error)));
}


void server_connection::startReading()
{
	mLogger.infoStream() << "starting asynchronous read...";

	mSocket->async_read_some(to_asio_buffer(mInputMsg),
							 decorate(
								 boost::bind(&server_connection::onRead,
											 shared_from(this),
											 placeholders::error,
											 placeholders::bytes_transferred)));
}




///////////////////// on* functions (async handlers) /////////////////////



void server_connection::onWrite(const error_code & ec, size_t bytes_transferred)
{
	mLogger.infoStream() << "write status: " << ec << ", "
							"message: " << ec.message() << ", "
							"bytes written: " << bytes_transferred;

	if (!ec)
	{
		startWaiting(boost::posix_time::milliseconds(mOutputMsg.timeout));
	}
}




void server_connection::onWait(const boost::system::error_code & ec)
{
	mLogger.infoStream() << "timer status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		startReading();
	}
}




void server_connection::onRead(const error_code & ec, size_t bytes_transferred)
{
	mLogger.infoStream() << "read status: " << ec << ", message: " << ec.message();

	if (!ec)
	{

		/// move current position
		mInputMsg.count += bytes_transferred;
		BOOST_ASSERT(mInputMsg.count <= mInputMsg.storage.size());

		if ((mInputMsg.count > 0) && (mInputMsg.storage[mInputMsg.count - 1] == 0))
		{
			std::string clientAnswer(mInputMsg.storage.begin(), mInputMsg.storage.begin() + (mInputMsg.count - 1));

			mLogger.infoStream() << "answer from client readed: [" << clientAnswer << "]";
		}
		else
		{
			mLogger.infoStream() << "received partial message, waiting end of message...";
			startReading();
		}
	}
}
