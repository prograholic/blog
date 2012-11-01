#include "application.h"

#include <iostream>


int main()
{
	try
	{
		application app;

		return app.run();
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
