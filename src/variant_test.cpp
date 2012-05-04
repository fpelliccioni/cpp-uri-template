// clang++ -std=c++11 variant_test.cpp
// g++ -std=c++11 variant_test.cpp

#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <vector>

#include "tmp_utils.hpp"



template <typename T>
struct Sizeof
{
	static constexpr size_t value = sizeof(T);
};


//reemplazada con std::alignment_of<>::value
//template <typename T>
//struct Alignof
//{
//	static constexpr size_t value = alignof(T);
//};



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

template <typename Derived, typename ...Ts>
struct other_variant_base
{
	void init() {} //workarround ... eliminate with metaprogramming
	void get()  {} //workarround ... eliminate with metaprogramming
};

template <typename Derived, typename T, typename ...Ts>
struct other_variant_base<Derived, T, Ts...> : other_variant_base<other_variant_base<Derived, T, Ts...>, Ts...> //private other_variant_base<Ts...>
{
	typedef other_variant_base<other_variant_base<Derived, T, Ts...>, Ts...> base;

	char* storage()
	{
		return static_cast<Derived*>(this)->storage();
	}

//	other_variant_base( T const& value )		//	//TODO: necesito "inheriting constructors"

	using base::init;
	void init( T const& value ) //constructor temporal replacement
	{
		auto p = storage();

		new(p) T(value);

		//std::cout << typeid(*this).name() << std::endl;
		std::cout << typeid(T).name() << ": " << value << std::endl;
	}

	using base::get;

	template <typename T2>
	typename std::enable_if<std::is_same<T, T2>::value, T>::type
	get()
	{
		auto p = storage();

		auto x = *(reinterpret_cast<T*>(p));

		std::cout << "x " << x << std::endl;

		return x;

		//std::cout << "-------------" << std::endl;
		//std::cout << "T " << typeid(T2).name() << std::endl;
		//std::cout << "T2 " << typeid(T2).name() << std::endl;
		//std::cout << typeid(*this).name() << std::endl;
	}



};


template <typename T, typename ...Ts>
struct other_variant : other_variant_base<other_variant<T, Ts...>, T, Ts...> 
{
	typedef other_variant_base<other_variant<T, Ts...>, T, Ts...> base;
	static constexpr size_t size_ = max<Sizeof, T, Ts...>::value;
	char storage_[size_];	//TODO: ver alignment

	char* storage()
	{
		return storage_;
	}

	~other_variant() 
	{
		//reinterpret_cast<const T*>(data)->~T();
	}
};

template <typename T, typename Variant>
T get( Variant & variant )
{
	return variant.get<T>();
}


//------------------------------------------------------------------------


template <typename Array, size_t Size>
void print( const Array (&array)[Size] )
{
	for (int i = 0; i<Size; ++i)
	{
		std::cout << (unsigned int)(unsigned char)array[i] << std::endl;
	}
}

void print_ptr( char * array, size_t size )
{
	for (int i = 0; i<size; ++i)
	{
		std::cout << (unsigned int)(unsigned char)array[i] << std::endl;
	}
}
//------------------------------------------------------------------------

struct my_type
{
	int a;
	int b;
	int c;
};

//------------------------------------------------------------------------

template <size_t Index, typename Elem, typename ...Ts>
struct find_helper {};

template <size_t Index, typename Elem, typename Current, typename ...Ts>
struct find_helper<Index, Elem, Current, Ts...>
{
	typedef typename std::conditional<
		std::is_same<Elem, Current>::value
		, std::integral_constant<size_t, Index>
		, typename find_helper<Index+1, Elem, Ts...>::type
	>::type type;
};

template <typename Elem, typename ...Ts>
struct find
{
	typedef typename find_helper<0, Elem, Ts...>::type type;
};

//------------------------------------------------------------------------



int main( /* int argc, char* argv[] */ )
{

	typedef find<int, double, std::string, int>::type ftype;

	std::cout << typeid(ftype).name() << std::endl;



	typedef other_variant<int, double> ov_type;

	//std::cout << typeid(ov_type).name() << std::endl;
	//std::cout << typeid(ov_type::base).name() << std::endl;
	//std::cout << typeid(ov_type::base::base).name() << std::endl;
	//std::cout << typeid(ov_type::base::base::base).name() << std::endl;
		
	ov_type ov;
	
	std::cout << ov.size_ << std::endl;
	std::cout << sizeof(ov) << std::endl;
	//std::cout << "ov.storage_: " << (unsigned int) ov.storage_ << std::endl;

	ov.init(15);
	std::cout << "get: " << get<int>(ov) << std::endl;
	//print(ov.storage_);

	ov.init(99.9);
	std::cout << "get: " << get<double>(ov) << std::endl;
	//print(ov.storage_);


	other_variant<int, double, std::string> ov2;
	std::cout << sizeof(ov2) << std::endl;

	ov2.init("fer");
	std::cout << "get: " << get<std::string>(ov2) << std::endl;


	std::cout << sizeof(my_type) << std::endl;
	std::cout << alignof(my_type) << std::endl;
	

	
	return 0;
}
