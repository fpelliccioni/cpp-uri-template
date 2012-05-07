// clang++ -std=c++11 json_test_2.cpp
// g++ -std=c++0x json_test_2.cpp

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>

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



struct my_simple_class 
{
};

template<typename First>
struct my_variant_base
{
	First data_;

	my_variant_base() = default;

	my_variant_base(First f)
		: data_(f)
	{}
};


template<typename First, typename Enable = void>
struct my_variant : my_variant_base<First>
{
	typedef my_variant_base<First> base;

	my_variant() = default;

	my_variant(First f)
		: base(f)
	{}

	template<typename T>
	my_variant(T t)
		: base(t)
	{}
};

template<typename First>
struct my_variant<First, typename std::enable_if<is_container<First>::value>::type> : my_variant_base<First>
{
	typedef my_variant_base<First> base;

	my_variant() = default;

	my_variant(First f)
		: base(f)
	{}

	template<typename T>
	my_variant(T t)
		: base(t)
	{}

	my_variant( std::initializer_list<typename First::value_type> il)
		: base(il)
	{}
};


int main( /* int argc, char* argv[] */ )
{
	my_variant<string> mv1;
	my_variant<string> mv2 = "fer";
	my_variant<string> mv3("fer");
	my_variant<string> mv4 = {'f', 'e', 'r'};


	my_variant<my_simple_class> mv5 = my_simple_class();

	my_variant<int> mv6= 64;


	my_variant<vector<string>> mv7 = {"fernando", "pelliccioni"};


	for (auto x : mv7.data_)
	{
		std::cout << x << std::endl;
	}



	return 0;
}
