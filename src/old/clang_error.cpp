//// clang++ -std=c++11 clang_error.cpp
//// g++ -std=c++0x clang_error.cpp
//
//#include <iostream>
//#include <type_traits>
//
//template <typename ...Ts>
//struct other_variant
//{
//	union U
//	{
//	} u;
//
//	void init() {} //workarround ... eliminate with metaprogramming
//	void get()  {} //workarround ... eliminate with metaprogramming
//
//};
//
//template <typename T, typename ...Ts>
//struct other_variant<T, Ts...> : other_variant<Ts...> //private other_variant<Ts...>
//{
//	typedef other_variant<Ts...> base;
//
//
//	union U
//	{
//		T e;
//		typename base::U bu;
//	} u;
//
//
//
//	using base::init;
//
//	void init( T const& value ) //constructor temporal replacement -- need inheriting constructors
//	{
//		u.e = value;
//	}
//
//	using base::get;
//
//	template <typename T2>
//	T get( typename std::enable_if<std::is_same<T, T2>::value, T>::type* dummy = 0 )
//	{
//		return u.e;
//	}
//
//};
//
//
//int main( /* int argc, char* argv[] */ )
//{
//	other_variant<int, double> ov;
//	ov.init(15.0);
//	std::cout << ov.get<double>() << std::endl;
//	std::cout << ov.get<int>() << std::endl;
//	//std::cout << ov.get<float>() << std::endl;			//Compile-time error -> OK
//
//	return 0;
//}
