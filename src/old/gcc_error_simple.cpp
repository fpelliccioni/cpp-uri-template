// g++ -std=c++11 gcc_error_simple.cpp
// g++ -DWITH_USING_DECLARATION -std=c++11 gcc_error_simple.cpp

#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
struct Base
{
	template <typename T2>
	typename std::enable_if<std::is_same<T, T2>::value, T>::type 
	get()
	{
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
	}
};


int main( /* int argc, char* argv[] */ )
{
	Derived<double> d;
	
	auto xxx = d.get<double>();
	//std::cout << typeid(xxx).name() << std::endl;
	
	auto yyy = d.get<int>();		// #ifndef WITH_USING_DECLARATION -> Compile-time error    -> GCC is behaving incorrectly. Base<int>::get<int>() should not be hidden
															// #ifdef  WITH_USING_DECLARATION -> No Compile-time error -> GCC is behaving incorrectly. Base<int>::get<int>() must be hidden.
	//std::cout << typeid(yyy).name() << std::endl;

	return 0;
}
