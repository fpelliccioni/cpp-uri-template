// clang++ -std=c++11 initlist_rvalue_test.cpp
// clang++ -std=c++11 -stdlib=libc++ initlist_rvalue_test.cpp

#include <iostream>
#include <initializer_list>
#include <map>
#include <string>
#include <utility>

template <typename T>
struct my_vector
{
	my_vector( )
	{
		std::cout << "my_vector - ctor" << std::endl;
	}

	my_vector( std::initializer_list<T> init_list )
    {
		std::cout << "my_vector - init list ctor" << std::endl;
    }

	my_vector( my_vector const& lvalue )
	{
		std::cout << "my_vector - copy ctor" << std::endl;
	}

	my_vector& operator=( my_vector const& lvalue )
	{
		std::cout << "my_vector - copy assignment op" << std::endl;
	}

	my_vector( my_vector && other )
	{
		std::cout << "my_vector - move ctor" << std::endl;
	}

	my_vector& operator=( my_vector&& rvalue )
	{
		std::cout << "my_vector - move assignment op" << std::endl;
	}

	~my_vector()
	{
		std::cout << "my_vector dtor" << std::endl;
	}
};



template <typename T, typename U>
struct my_pair
{
	T t_;
	U u_;

//	my_pair( T const& t, U const& u )
//		: t_( t ), u_( u )
//	{
//		std::cout << "pair ctor" << std::endl;
//	}

//	my_pair( T && t, U && u )
//		: t_( std::forward<T>(t) ), u_( std::forward<U>(u) )
//	{
//		std::cout << "pair ctor - move" << std::endl;
//	}

	template<typename T2, typename U2>
	my_pair(T2&& t, U2&& u)
		: t_( std::forward<T2>(t) ), u_( std::forward<U2>(u) )
	{
		std::cout << "pair ctor - move - template" << std::endl;
	}

	my_pair( my_pair const& other )
		: t_(other.t_), u_(other.u_)
	{
		std::cout << "pair copy ctor" << std::endl;
	}

	my_pair( my_pair && other )
		: t_( std::move(other.t_)), u_( std::move(other.u_))
	{
		std::cout << "pair move ctor" << std::endl;
	}

	~my_pair()
	{
		std::cout << "pair dtor" << std::endl;
	}

};


using namespace std;


typedef std::pair<std::string, my_vector<string> > pair_type_4;
typedef my_pair<std::string, my_vector<string> > pair_type_5;

int main( /* int argc, char* argv[] */ )
{

	//pair_type_4 p6_b ("list",  { "val1", "val2", "val3" }  );
	//pair_type_4 p7_b ("list", my_vector<string>() );
	//pair_type_5 p6 ("list", { "val1", "val2", "val3" } );
	//pair_type_5 p7 ("list", my_vector<string>() );


	return 0;
}
