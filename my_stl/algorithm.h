#ifndef MY_STL_ALGORITHM_H
#define MY_STL_ALGORITHM_H


namespace my_stl
{
	template <typename InputIteratorT, typename FunctionT>
	FunctionT for_each(InputIteratorT first, InputIteratorT last, FunctionT func)
	{
		for ( ; first != last; ++first)
		{
			func(*first);
		}

		return func;
	}




	template <typename InputIteratorT, typename ValueT>
	InputIteratorT find(InputIteratorT first, InputIteratorT last, ValueT value)
	{
		for ( ; first != last; ++first)
		{
			if (*first == value)
			{
				break;
			}
		}

		return first;
	}




	template <typename InputIteratorT, typename FunctionT>
	InputIteratorT find_if(InputIteratorT first, InputIteratorT last, FunctionT predicate)
	{
		for ( ; first != last; ++first)
		{
			if (predicate(*first))
			{
				break;
			}
		}

		return first;
	}
}




#endif /* MY_STL_ALGORITHM_H */
