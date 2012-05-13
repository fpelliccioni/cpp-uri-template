// clang++ -std=c++11 json_test.cpp
// g++ -std=c++0x json_test.cpp

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

#include "variant.hpp"

using namespace std;

typedef std::map<std::string, std::string> simple_map;
typedef std::vector<std::string> vector_type;
//using value_type = variant<std::string, vector_type>;
typedef variant<vector_type> value_type ;

//using json_map = std::unordered_map<std::string, value_type>;
//using json_map = std::map<std::string, value_type>;
typedef std::map<std::string, vector_type> json_map;

template <typename T>
struct my_vector_type
{
	my_vector_type(initializer_list<T> init_list)
    {
		std::cout << typeid(init_list).name() << endl;
    }

};

template <typename First>
struct my_variant_type_base_normal
{
	my_variant_type_base_normal( First first )
		//: data_(first)
    {
		std::cout << "my_variant_type_base_normal(First first)" << endl;
		std::cout << typeid(first).name() << endl;
    }

//	template <typename T>
//	my_variant_type_base_normal( T t )
//		//: data_(t)
//	{
//		std::cout << "my_variant_type_base_normal( T t)" << endl;
//		std::cout << typeid(t).name() << endl;
//	}

};

template <typename First>
struct my_variant_type : my_variant_type_base_normal<First>
{
	typedef my_variant_type_base_normal<First> base;

	using base::my_variant_type_base_normal;


	First data_;

	//my_variant_type() {};	//= default;

//	my_variant_type( First first )
//		: data_(first)
//    {
//		std::cout << "normal ctor" << endl;
//		std::cout << typeid(first).name() << endl;
//    }
//
//	template <typename T>
//	my_variant_type( T t )
//		: data_(t)
//    {
//		std::cout << "convertion ctor" << endl;
//    }
//
//
//	my_variant_type( initializer_list<typename First::value_type> init_list )		//TODO: value type traits
//		: data_(init_list)
//    {
//		std::cout << "initializer list ctor" << endl;
//    }


//	my_variant_type& operator=( First first )
//    {
//		data_ = first;
//		std::cout << "normal assig op" << endl;
//		std::cout << typeid(first).name() << endl;
//
//
//		return *this;
//    }

//	void init( First first )							//ctor emulator
//    {
//		//data_ = first;
//
//		std::cout << "normal init" << endl;
//		std::cout << typeid(first).name() << endl;
//    }

};




struct my_simple_class
{
};




int main( /* int argc, char* argv[] */ )
{
	//my_variant_type<int> mvt1 = 15;
	//my_variant_type<my_simple_class> mvt2 = my_simple_class();

//	my_variant_type<string> mvt3 = "fer";
//	my_variant_type<string> mvt4 {'f', 'e', 'r'};
//	my_variant_type<string> mvt5("fer");


//	my_variant_type<string> mvt6;
//	my_variant_type<string> mvt7;
//
//	mvt6 = "fer";
//	mvt7 = {'f', 'e', 'r'};


//	my_variant_type<string> mvt8;
//	my_variant_type<string> mvt9;
//
//	mvt8.init("fer");
//	mvt9.init({'f', 'e', 'r'});


	return 0;
}
