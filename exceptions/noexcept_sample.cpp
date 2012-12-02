#include "noexcept_sample.h"

#include <vector>
#include <iostream>

template <typename InputTypeT>
void func() noexcept(noexcept(InputTypeT())) {
	InputTypeT var;
	/// do smth with var
	std::cout << "func called, object size: " << sizeof(var) << std::endl;
}

void noexceptSample() {
	std::cout << "noexcept int():         " << noexcept(int()) << std::endl;
	std::cout << "noexcept vector<int>(): " << noexcept(std::vector<int>()) << std::endl << std::endl;

	/// @note function is not actually called
	std::cout << "noexcept func<int>:         " << noexcept(func<int>()) << std::endl;
	std::cout << "noexcept func<vector<int>>: " << noexcept(func<std::vector<int>>()) << std::endl;
}
