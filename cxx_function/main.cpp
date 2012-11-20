#include <iostream>








template <typename ReturnType, typename ... ArgumentTypes>
class typed_function
{
public:


	template <typename FunctionT>
	typed_function(FunctionT f)
		: mInvoker(new templated_function_holder<FunctionT>(f))
	{

	}


	~typed_function()
	{
		delete mInvoker;
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


		virtual function_holder_base * clone() = 0;


	private:
		function_holder_base(const function_holder_base & );
		void operator = (const function_holder_base &);

	};


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


		virtual self_type * clone()
		{
			return new self_type(mFunction);
		}


	private:

		FunctionT mFunction;
	};




	function_holder_base * mInvoker;

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


int main()
{
	typedef typed_function<int> int_function_t;
	int_function_t f1(func1);

	cout << "calling function with signature int (void):               " <<  f1() << std::endl;




	typedef typed_function<int, const char * , int> int_function_with_two_args_t;
	int_function_with_two_args_t f2(func2);

	char x = 10;

	cout << "calling function with signature int (const char * , int): " <<  f2(&x, 20) << std::endl;


	return 0;
}
