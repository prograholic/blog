#include "SimpleClass.h"

#include <iostream>

SimpleClass::SimpleClass()
{
	std::cout << "SimpleClass::ctor" << std::endl;
}


SimpleClass::~SimpleClass()
{
	std::cout << "SimpleClass::dtor" << std::endl;
}
