#include "ClassOwner.h"

#include "SimpleClass.h"

ClassOwner::ClassOwner(): mImpl(new SimpleClass)
{
}

/*
ClassOwner::~ClassOwner()
{
	/// needed only for correct destruction of auto_ptr
}
*/