// clang++ -std=c++11 variant_test.cpp
// g++ -std=c++11 variant_test.cpp

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>

#include "variant.hpp"

using namespace std;


template<typename Container, typename = void>
struct is_container : std::false_type
{ };

template<typename A, A, A>
struct is_of_type { typedef void type; };

template<typename C>
struct is_container<C,
	typename is_of_type<
	typename C::iterator(C::*)(),
	&C::begin,
	&C::end>::type> : std::is_class<C>
{};


//template <typename T>
//struct Base
//{
//
//	template <typename T2>
//	struct internal
//	{
//		static void f()
//		{
//			std::cout << "f()" << std::endl;
//		}
//	};
//
//	void a()
//	{
//		//internal::f();
//		internal<int>::f();
//	}
//
//};
//
//template <typename T>
//struct Derived : Base<T>
//{
//	//typedef Base<T> base;
//
//	//using base::internal;
//
//	void b()
//	{
//		Base<T>::template internal<int>::f();
//	}
//};

//template <typename First, typename Enabled = void, typename... Ts>
//struct TestDefaults;
//
//template <typename First, typename... Ts>
//struct TestDefaults<First, typename std::enable_if<is_container<First>::value>::type, Ts...>
//{
//};
//
//template <typename First, typename... Ts>
//struct TestDefaults<First, typename std::disable_if<is_container<First>::value>::type, Ts...>
//{
//};


template <typename T, typename IsContainer>
struct TestDetails;

template <typename T>
struct TestDetails<T, std::false_type>
{
	void f()
	{
		std::cout << "f() NOT" << std::endl;
	}

};

template <typename T>
struct TestDetails<T, std::true_type>
{
	void f()
	{
		std::cout << "f() CONTAINER" << std::endl;
	}
};


template <typename T, typename... Ts>
struct Test : TestDetails< T, typename is_container<T>::type >
{
};

template <typename T>
using Test2 = TestDetails< T, typename is_container<T>::type >;

//TODO: se necesita C++11 inherited constructors!!!!!!!


int main( /* int argc, char* argv[] */ )
{
//	Derived<int> d;
//	d.a();
//	d.b();


	//TestDefaults<int> td;

	Test<int> ti;
	ti.f();


	Test<std::string> ts;
	ts.f();


	Test2<int> ti2;
	ti2.f();


	Test2<std::string> ts2;
	ts2.f();



	typedef variant_base<int, double, string> my_variant_1;

	my_variant_1 mv1 = "fer";
	cout << get<string>(mv1) << endl;
	//cout << get<int>(mv1) << endl;		//run time error






	variant<int, double, string> mv2 = "fer";
	//cout << get<string>(mv2) << endl;


	//variant<int, double, string> mv3 = {'f', 'e', 'r'};



	//typedef variant<int, double, string, vector<int> > my_variant_2;

	//my_variant_2 mv2 = "fernando";
	//cout << get<string>(mv2) << endl;

	//my_variant_2 mv3 ( { 1, 2, 3, 4, 5, 6, 7 } );
	//auto xxx = get<vector<int>>(mv3);

	//for (auto x : xxx)
	//{
	//	cout << x << endl;
	//}

	////my_variant_1 mv4 ( { 1, 2, 3, 4, 5, 6, 7 } );		//Compile time error
	////my_variant_1 mv5 ( { "fer" } );		//Compile time error
	////my_variant_1 mv6 { "fer" };		//Compile time error
	////my_variant_1 mv7 = { "fer" };		//Compile time error



	return 0;
}
