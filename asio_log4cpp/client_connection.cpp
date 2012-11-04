#include "client_connection.h"

#include "connection_manager.h"

using namespace boost::asio;
using namespace boost::system;
using namespace boost::posix_time;

client_connection::client_connection(connection_manager_ptr connectionManager, socket_ptr connection)
	: connection_base(connectionManager),
	  mSocket(connection),
	  mInputMsg(),
	  mOutputMsg("GOODBYE"),
	  mLogger(log4cpp::Category::getInstance("client.connection")),
	  mTimer(connection->get_io_service()),
	  mNdc("client_" + boost::lexical_cast<std::string>(connectionManager->nextCounter()))
{

}


void client_connection::start()
{
	startReading();
}


void client_connection::stop()
{
	mSocket->close();
	mTimer.cancel();
}


void client_connection::startReading()
{
	mLogger.infoStream() << "starting asynchronous reading...";

	mSocket->async_read_some(to_asio_buffer(mInputMsg),
							 decorate<NdcDecorator>(
								 boost::bind(&client_connection::onRead,
											 shared_from(this),
											 placeholders::error,
											 placeholders::bytes_transferred),
								 mNdc));
}



void client_connection::startWaiting(const boost::posix_time::time_duration & timeout)
{
	mLogger.infoStream() << "starting asynchronous timeout " << timeout << " ...";

	mTimer.expires_from_now(timeout);
	mTimer.async_wait(
				decorate<NdcDecorator>(
					boost::bind(&client_connection::onWait,
								shared_from(this),
								placeholders::error),
					mNdc));
}


void client_connection::startWriting()
{
	mLogger.infoStream() << "starting asynchronous write...";

	async_write(*mSocket,
				to_asio_buffer(mOutputMsg),
				decorate<NdcDecorator>(
					boost::bind(&client_connection::onWrite,
								shared_from(this),
								placeholders::error,
								placeholders::bytes_transferred),
					mNdc));
}








///////////////////// on* functions (async handlers) /////////////////////



void client_connection::onRead(const error_code & ec, size_t bytes_transferred)
{
	mLogger.infoStream() << "read status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		/// move current position
		mInputMsg.count += bytes_transferred;
		BOOST_ASSERT(mInputMsg.count <= mInputMsg.storage.size());

		if ((mInputMsg.count > 0) && (mInputMsg.storage[mInputMsg.count - 1] == 0))
		{
			std::string serverAnswer(mInputMsg.storage.begin(), mInputMsg.storage.begin() + (mInputMsg.count - 1));
			mLogger.infoStream() << "answer from server readed: [" << serverAnswer << "]";

			size_t msec = boost::lexical_cast<size_t>(serverAnswer);
			startWaiting(milliseconds(msec));

		}
		else
		{
			mLogger.infoStream() << "received partial message, waiting end of message...";
			startReading();
		}
	}
}



void client_connection::onWait(const error_code & ec)
{
	mLogger.infoStream() << "timer status: " << ec << ", message: " << ec.message();

	if (!ec)
	{
		startWriting();
	}
}


void client_connection::onWrite(const error_code & ec, size_t bytes_transferred)
{
	mLogger.infoStream() << "write status: " << ec << ", "
							"message: " << ec.message() << ", "
							"bytes written: " << bytes_transferred;
}
