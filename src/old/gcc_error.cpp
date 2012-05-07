//// g++ -std=c++11 gcc_error.cpp
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
//	typename std::enable_if<std::is_same<T, T2>::value, T>::type
//	get()
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
//	std::cout << ov.get<int>() << std::endl;			//Must reject this line. According to [namespace.udecl]p15
//
//	return 0;
//}
