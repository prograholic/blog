#include <iostream>
#include <memory>


#include <functional>



namespace detail
{
	template <typename FirstType, typename ... RestTypes>
	struct first_
	{
		typedef FirstType type;
	};
}




template <typename UnusedType>
class function;




template <typename ReturnType, typename ... ArgumentTypes>
class function <ReturnType (ArgumentTypes ...)>
{
public:

	typedef ReturnType signature_type (ArgumentTypes ...);

	function()
		: mInvoker()
	{}


	template <typename FunctionT>
	function(FunctionT f)
		: mInvoker(new free_function_holder<FunctionT>(f))
	{

	}

	template <typename FunctionType, typename ClassType>
	function(FunctionType ClassType::* f)
		: mInvoker(new member_function_holder<FunctionType, ArgumentTypes ...>(f))
	{}


	function(const function & other)
		: mInvoker(other.mInvoker->clone())
	{

	}

	function & operator = (const function & other)
	{
		mInvoker = other.mInvoker->clone();
	}

	ReturnType operator ()(ArgumentTypes ... args)
	{
		return mInvoker->invoke(args ...);
	}


private:


	class function_holder_base
	{
	public:

		function_holder_base()
		{
		}

		virtual ~function_holder_base()
		{
		}

		virtual ReturnType invoke(ArgumentTypes ... args) = 0;

		virtual std::auto_ptr<function_holder_base> clone() = 0;

	private:
		function_holder_base(const function_holder_base & );
		void operator = (const function_holder_base &);
	};


	typedef std::auto_ptr<function_holder_base> invoker_t;


	template <typename FunctionT>
	class free_function_holder : public function_holder_base
	{
	public:

		free_function_holder(FunctionT func)
			: function_holder_base(),
			  mFunction(func)
		{

		}

		virtual ReturnType invoke(ArgumentTypes ... args)
		{
			return mFunction(args ...);
		}


		virtual invoker_t clone()
		{
			return invoker_t(new free_function_holder(mFunction));
		}

	private:

		FunctionT mFunction;
	};


	template <typename FunctionType, typename ClassType, typename ... RestArgumentTypes>
	class member_function_holder : public function_holder_base
	{
	public:


		typedef FunctionType ClassType::* member_function_signature_t;

		member_function_holder(member_function_signature_t f)
			: mFunction(f)
		{}

		virtual ReturnType invoke(ClassType obj, RestArgumentTypes ... restArgs)
		{
			return (obj.*mFunction)(restArgs ...);
		}

		virtual invoker_t clone()
		{
			return invoker_t(new member_function_holder(mFunction));
		}

	private:
		member_function_signature_t mFunction;
	};

	invoker_t mInvoker;
};


int func1()
{
	return 0;
}

int func2(const int * x, int y)
{
	return (*x) + y;
}

using std::cout;
using std::endl;

void check1()
{
	typedef function<int (const int * , int)> int_function_with_two_args_t;
	int_function_with_two_args_t f2(func2);

	int x = 10;
	cout << "calling function with signature int (const int * , int):              " <<  f2(&x, 20) << endl;
}



void check2()
{
	typedef function<int (void)> int_function_t;
	int_function_t f1(func1);

	cout << "calling function with signature int (void):                           " <<  f1() << endl;

	int_function_t f2;


	f2 = f1;
	cout << "calling function after assignment operator with signature int (void): " <<  f2() << endl;


	int_function_t f3(f2);
	cout << "calling function after copying ctor with signature int (void):        " <<  f3() << endl;
}


struct Foo
{
	int smth(int x)
	{
		return x + 1;
	}
};







void check3()
{
	typedef function<int (Foo, int)> member_function_t;

	member_function_t f1 = &Foo::smth;


	Foo foo;
	cout << "calling member function with signature int (int):                     " <<  f1(foo, 5) << endl;
}



int main()
{
	check1();
	check2();
	check3();

	return 0;
}
