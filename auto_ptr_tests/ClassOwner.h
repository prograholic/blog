#ifndef CLASSOWNER_H
#define CLASSOWNER_H

//#include <boost/smart_ptr/scoped_ptr.hpp>
#include <memory>

class ClassOwner
{
public:
	ClassOwner();
//	~ClassOwner();

private:
	//boost::scoped_ptr<class SimpleClass> mImpl;
	std::auto_ptr<class SimpleClass> mImpl;
};

#endif // CLASSOWNER_H
