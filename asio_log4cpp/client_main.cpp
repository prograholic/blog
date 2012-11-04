#include "application.h"

#include "client.h"

#include <iostream>


int main()
{
	try
	{
		template_runnable_factory<client> clientFactory;
		application app(clientFactory);


		const std::string address = "0.0.0.0";
		const std::string port = "12345";

		return app.run(address, port);
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "UNKNOWN ERROR" << std::endl;
		return 2;
	}
}
