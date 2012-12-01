#include "noexcept_sample.h"

#include <vector>
#include <iostream>

using namespace std;




template <typename InputTypeT>
void func() noexcept(noexcept(InputTypeT())) {
	InputTypeT var;
	/// do smth with var
	cout << "func called, object size: " << sizeof(var) << endl;
}



void noexceptSample() {
	cout << "noexcept int():         " << noexcept(int()) << endl;
	cout << "noexcept vector<int>(): " << noexcept(vector<int>()) << endl << endl;

	/// @note function is not actually called
	cout << "noexcept func<int>:         " << noexcept(func<int>()) << endl;
	cout << "noexcept func<vector<int>>: " << noexcept(func<vector<int>>()) << endl;
}
