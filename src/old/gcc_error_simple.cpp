// g++ -std=c++0x gcc_error_simple.cpp
// g++ -DWITH_USING_DECLARATION -std=c++0x gcc_error_simple.cpp

// clang++ -std=c++11 gcc_error_simple.cpp
// clang++ -DWITH_USING_DECLARATION -std=c++11 gcc_error_simple.cpp

#include <iostream>
#include <type_traits>

template <typename T>
struct Base
{
	template <typename T2>
	typename std::enable_if<std::is_same<T, T2>::value, T>::type
	get()
	{
		return T2();
	}
};

template <typename T>
struct Derived : Base<int>
{
	typedef Base<int> base;

#ifdef WITH_USING_DECLARATION
	using base::get;
#endif

	template <typename T2>
	typename std::enable_if<std::is_same<T, T2>::value, T>::type
	get()
	{
		return T2();
	}
};

void f(int i)
{
	std::cout << "f(int)" << std::endl;
}

void f(double d)
{
	std::cout << "f(double)" << std::endl;
}

int main( /* int argc, char* argv[] */ )
{
	Derived<double> d;

	auto xxx = d.get<double>();
	auto yyy = d.get<int>();	// #ifndef WITH_USING_DECLARATION -> Compile-time error    -> GCC is behaving Correctly!!! Base<int>::get<int>() is hidden!
								// #ifdef  WITH_USING_DECLARATION -> No Compile-time error -> GCC is behaving incorrectly. Base<int>::get<int>() must be hidden.

	f(xxx);
	f(yyy);


	return 0;
}
