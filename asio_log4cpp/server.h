#ifndef SERVER_H
#define SERVER_H

#include "common.h"

class server : private boost::noncopyable
{
public:
	server(boost::asio::io_service & io);


private:

	boost::asio::io_service & mIo;
};

#endif // SERVER_H
