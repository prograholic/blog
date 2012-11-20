#include <iostream>

#include <memory>






template <typename ReturnType, typename ... ArgumentTypes>
class typed_function
{
public:


	typed_function()
		: mInvoker()
	{}


	template <typename FunctionT>
	typed_function(FunctionT f)
		: mInvoker(new templated_function_holder<FunctionT>(f))
	{

	}


	typed_function(const typed_function & other)
		: mInvoker(other.mInvoker->clone())
	{

	}

	typed_function & operator = (const typed_function & other)
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
	class templated_function_holder : public function_holder_base
	{
	public:

		templated_function_holder(FunctionT func)
			: function_holder_base(),
			  mFunction(func)
		{

		}

		typedef templated_function_holder<FunctionT> self_type;

		virtual ReturnType invoke(ArgumentTypes ... args)
		{
			return mFunction(args ...);
		}


		virtual invoker_t clone()
		{
			return invoker_t(new self_type(mFunction));
		}


	private:

		FunctionT mFunction;
	};

	invoker_t mInvoker;
};





int func1()
{
	return 0;
}



int func2(const char * x, int y)
{
	return (*x) + y;
}




using std::cout;
using std::endl;



void check1()
{
	typedef typed_function<int> int_function_t;
	int_function_t f1(func1);

	cout << "calling function with signature int (void):                           " <<  f1() << std::endl;

	int_function_t f2;


	f2 = f1;
	cout << "calling function after assignment operator with signature int (void): " <<  f2() << std::endl;


	int_function_t f3(f2);
	cout << "calling function after copying ctor with signature int (void):        " <<  f3() << std::endl;
}



void check2()
{
	typedef typed_function<int, const char * , int> int_function_with_two_args_t;
	int_function_with_two_args_t f2(func2);

	char x = 10;

	cout << "calling function with signature int (const char * , int):             " <<  f2(&x, 20) << std::endl;
}

int main()
{
	check1();
	check2();

	return 0;
}
