// g++     -I"D:\Program Files\Boost\boost_1_49_0" -std=c++11 test.cpp
// clang++ -I$BOOST_ROOT -std=c++11 test.cpp
// clang++ -I$BOOST_ROOT -std=c++11 -stdlib=libc++ test.cpp				--runtime error

// g++     -std=c++11 variant_test.cpp



#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include <type_traits>

#include <vector>



//------------------------------------------------------------------------

//template <typename T1, typename T2>
//struct my_variant_type
//{
//	template <typename T>
//	my_variant_type( T const& t )
//	{
//		std::cout << typeid(t).name() << std::endl;
//	}
//
//	template <typename T>
//	my_variant_type( std::initializer_list<T> const& t )
//	{
//		std::cout << typeid(t).name() << std::endl;
//	}
//};


//------------------------------------------------------------------------

template <typename ...Ts>
struct other_variant
{
	union U
	{
	} u;

	void init() {} //workarround ... eliminate with metaprogramming
	void get()  {} //workarround ... eliminate with metaprogramming

};

template <typename T, typename ...Ts>
struct other_variant<T, Ts...> : other_variant<Ts...> //private other_variant<Ts...>
{
	typedef other_variant<Ts...> base;

//private:
	//T head_;

	union U
	{
		T e;
		typename base::U bu;
	} u;

//	other_variant( )
//	{
//	}

//	//TODO: necesito "inheriting constructors"
//	other_variant( T const& value )
//	{
//		u.e = value;
//
//		std::cout << typeid(*this).name() << std::endl;
//		std::cout << typeid(T).name() << ": " << u.e << std::endl;
//	}

	using base::init;

	//testeado algo similar usando una member function en vez de un constructor
	void init( T const& value ) //constructor temporal replacement
	{
		u.e = value;
		std::cout << typeid(*this).name() << std::endl;
		std::cout << typeid(T).name() << ": " << u.e << std::endl;
	}

	using base::get;

	template <typename T2>
	typename std::enable_if<std::is_same<T, T2>::value, T>::type
	get()
	{
		//typedef typename std::enable_if<std::is_same<T, T2>::value, T>::type aver;

		std::cout << "-------------" << std::endl;
		std::cout << "T " << typeid(T2).name() << std::endl;
		std::cout << "T2 " << typeid(T2).name() << std::endl;
		std::cout << "std::is_same<T, T2>::value " << std::is_same<T, T2>::value << std::endl;
		//std::cout << "aver " << typeid(aver).name() << std::endl;

		std::cout << typeid(*this).name() << std::endl;


//		std::cout << "T2 " << typeid(T2).name() << std::endl;
//		std::cout << typeid(T).name() << ": " << u.e << std::endl;

		return u.e;
	}

};



//------------------------------------------------------------------------

int main( /* int argc, char* argv[] */ )
{

	typedef other_variant<int, double> ov_type;

	ov_type ov;
	other_variant<int> ov2;
	other_variant<> ov3;

//	std::cout << sizeof(ov3) << std::endl;
//	std::cout << sizeof(ov2) << std::endl;
//	std::cout << sizeof(ov) << std::endl;
//
//	std::cout << sizeof(ov.u) << std::endl;
//	std::cout << sizeof(ov.base::u) << std::endl;
//	std::cout << sizeof(ov.base::base::u) << std::endl;
//
//
//
//	std::cout << typeid(ov.u.e).name() << std::endl;
//	std::cout << typeid(ov.base::u.e).name() << std::endl;


//	other_variant<int, double> ob4 (15);
//	other_variant<int, double> ob5 (99.9);






//	other_variant<int, double> ob4;
//	ob4.init(15);
//
//	other_variant<int, double> ob5;
//	ob5.init(99.9);
//
//
//	std::cout << ob4.get<int>() << std::endl;
//	//std::cout << ob5.get<double>() << std::endl;





	other_variant<int, double> ob6;
	ob6.init(15.0);
	std::cout << ob6.get<double>() << std::endl;
	std::cout << ob6.get<int>() << std::endl;




//	union U
//	{
//		int i;
//	};
//
//	std::cout << sizeof(U) << std::endl;
//
//	union U2
//	{
//		int i;
//		float f;
//	};
//
//	std::cout << sizeof(U2) << std::endl;
//
//	union U3
//	{
//		int i;
//		float f;
//		U2 u2;
//	};
//
//	std::cout << sizeof(U3) << std::endl;
//
//
//	union U4
//	{
//		double d;
//		U3 u3;
//	};
//
//	std::cout << sizeof(U4) << std::endl;
//
//	U4 u4;
//
//	u4.u3.u2.i = 654;
//	std::cout << u4.u3.u2.i << std::endl;
//	std::cout << u4.d << std::endl;



	//------------------------------------------------------------------------


	return 0;
}
