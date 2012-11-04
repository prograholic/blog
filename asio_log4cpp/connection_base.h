#ifndef CONNECTION_BASE_H
#define CONNECTION_BASE_H

#include <boost/noncopyable.hpp>

#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>



typedef boost::shared_ptr<class connection_manager> connection_manager_ptr;
typedef boost::weak_ptr<class connection_manager> connection_manager_weak_ptr;

class connection_base : public boost::enable_shared_from_this<connection_base>
{
public:
	connection_base(connection_manager_ptr connectionManager);

	~connection_base();

	virtual void start() = 0;

	virtual void stop() = 0;

	template <typename ChildT>
	boost::shared_ptr<ChildT> shared_from(ChildT * /* self */)
	{
		/// @note self does not used actually, we use only type information of `self`
		return boost::static_pointer_cast<ChildT>(shared_from_this());
	}

private:
	connection_manager_weak_ptr mConnectionManager;
};



typedef boost::shared_ptr<connection_base> connection_base_ptr;
typedef boost::weak_ptr<connection_base> connection_base_weak_ptr;

#endif // CONNECTION_BASE_H
