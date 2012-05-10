// clang++ -std=c++11 json_test.cpp
// clang++ -std=c++11 -stdlib=libc++ json_test.cpp
// g++ -std=c++0x json_test.cpp
// g++ -std=c++11 json_test.cpp

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <typeinfo>
#include <utility>

#include "mpl.hpp"



//TODO: details
template <typename T>
struct Sizeof
{
	static constexpr size_t value = sizeof(T);
};

//TODO: details
template <typename T>
struct Alignof
{
	static constexpr size_t value = alignof(T);
};


//TODO: this could be improved with "inheriting constructor" language feature compiler support
//       could be constructed and variant type with initializer list
struct simple_json
{
	typedef std::string string_type;
	typedef std::vector<string_type> vector_type;
	typedef std::map<string_type, string_type> map_type;

	enum class storage_type_enum { string, vector, map, nil };


private:
	static constexpr size_t size_ = max<Sizeof, string_type, vector_type, map_type>::value;

	//alignas(max<Alignof, string_type, vector_type, map_type>::value) char storage_[size_];	//not supported by GCC 4.7.1
	char storage_[size_];
	
	storage_type_enum storage_type_ = storage_type_enum::nil;


	template <typename T>
	void construct( T&& t )
	{
		typedef typename std::remove_reference<T>::type type;
		new(storage_) type(std::forward<T>(t));
	}

	template <typename T>
	void destroy( T& t ) const
	{
		t.~T();
	}


public:

	simple_json( string_type&& val )		// explicit  ??
	{
		std::cout << "ctor 1" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::string;
	}

	simple_json( vector_type&& val )
	{
		std::cout << "ctor 2" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::vector;
	}

	simple_json( map_type&& val )
	{
		std::cout << "ctor 3" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::map;
	}

	template <size_t Size>
	simple_json( const typename string_type::value_type (&array)[Size] )
	{
		std::cout << "ctor 4" << std::endl;

		construct<string_type>(array);
		storage_type_ = storage_type_enum::string;
	}

	simple_json( std::initializer_list<typename string_type::value_type> init_list )
    {
		std::cout << "ctor 5" << std::endl;

		construct<string_type>(init_list);
		storage_type_ = storage_type_enum::string;
    }

	simple_json( std::initializer_list<typename vector_type::value_type> init_list )
    {
		std::cout << "ctor 6" << std::endl;

		construct<vector_type>(init_list);
		storage_type_ = storage_type_enum::vector;
    }

	simple_json( std::initializer_list<typename map_type::value_type> init_list )
    {
		std::cout << "ctor 7" << std::endl;

		//std::cout << "map: " << std::endl;
//		construct<vector_type>(init_list);
		storage_type_ = storage_type_enum::map;
    }


	//TODO: copy and move

//	simple_json( simple_json const& other )
//	{
//		switch(other.storage_type_)
//		{
//			case storage_type_enum::string:
//				std::cout << "copy ctor string" << std::endl;
//				construct( *reinterpret_cast<const string_type*>(other.storage_) );
//				break;
//			case storage_type_enum::vector:
//				std::cout << "copy ctor vec" << std::endl;
//				construct( *reinterpret_cast<const vector_type*>(other.storage_) );
//				break;
//			case storage_type_enum::map:
//				std::cout << "copy ctor map" << std::endl;
//				construct( *reinterpret_cast<const map_type*>(other.storage_) );
//				break;
//			case storage_type_enum::nil:
//			default:
//				std::cout << "ERROR copy ctor nil" << std::endl;
//				break;
//		}
//
//		storage_type_ = other.storage_type_;
//	}

	simple_json( simple_json && other )
	{
		switch(other.storage_type_)
		{
			case storage_type_enum::string:
				std::cout << "move ctor string" << std::endl;
				construct( std::move(*reinterpret_cast<string_type*>(other.storage_)) );
				break;
			case storage_type_enum::vector:
				std::cout << "move ctor vec" << std::endl;
				construct( std::move(*reinterpret_cast<vector_type*>(other.storage_)) );
				break;
			case storage_type_enum::map:
				std::cout << "move ctor map" << std::endl;
				construct( std::move(*reinterpret_cast<map_type*>(other.storage_)) );
				break;
			case storage_type_enum::nil:
			default:
				std::cout << "ERROR move ctor nil" << std::endl;
				break;
		}

		storage_type_ = other.storage_type_;
		other.storage_type_ = storage_type_enum::nil;
	}




	storage_type_enum get_type() const
	{
		return storage_type_;
	}


//	template <typename T, typename Dummy = void>
//	struct getter;
//
//	template <typename Dummy>
//	struct getter<string_type, Dummy>
//	{
//		const string_type & operator()( storage_type_enum storage_type, const char (&storage)[size_] )
//		{
//			if (storage_type == storage_type_enum::string)
//			{
//				return *reinterpret_cast<const string_type*>(storage);
//			}
//			else
//			{
//				throw std::exception();
//			}
//		}
//	};
//
//	template <typename T>
//	const T& get() const
//	{
//		return getter<T>()(storage_type_, storage_);
//	}

	~simple_json()
	{
		switch(storage_type_)
		{
			case storage_type_enum::string:
				std::cout << "destroy string" << std::endl;
				destroy( *reinterpret_cast<string_type*>(storage_) );
				break;
			case storage_type_enum::vector:
				std::cout << "destroy vec" << std::endl;
				destroy( *reinterpret_cast<vector_type*>(storage_) );
				break;
			case storage_type_enum::map:
				std::cout << "destroy map" << std::endl;
				destroy( *reinterpret_cast<map_type*>(storage_) );
				break;
			case storage_type_enum::nil:
			default:
				std::cout << "ERROR destroy nil" << std::endl;
				break;
		}
	}

};

//template <typename T>
//const T& get( simple_json sj )	//TODO: const?
//{
//	return sj.get<T>();
//}



std::string operator"" _s (const char* p, size_t n)	// std::string literal
{
	return std::string(p,n);	// requires free store allocation
}



template <typename T>
struct my_vector_type
{
	my_vector_type( )
	{
		std::cout << "my_vector_type ctor" << std::endl;
	}

	my_vector_type( std::initializer_list<T> init_list )
    {
		std::cout << "my_vector_type init list ctor" << std::endl;
    }


	my_vector_type( my_vector_type const& other )
	{
		std::cout << "my_vector_type copy ctor" << std::endl;
	}

	my_vector_type( my_vector_type && other )
	{
		std::cout << "my_vector_type move ctor" << std::endl;
	}

	~my_vector_type()
	{
		std::cout << "my_vector_type dtor" << std::endl;
	}

};


struct my_simple_class
{
	int data_ = 13;

	my_simple_class( )
	{
		std::cout << "my_simple_class ctor" << std::endl;
	}

	my_simple_class( my_simple_class const& other )
	{
		std::cout << "my_simple_class copy ctor" << std::endl;
	}

	my_simple_class( my_simple_class && other )
	{
		std::cout << "my_simple_class move ctor" << std::endl;
	}

	~my_simple_class()
	{
		std::cout << "my_simple_class dtor" << std::endl;
	}
};


template <typename T, typename U>
struct my_pair_type
{
	T t_;
	U u_;


	my_pair_type( T const& t, U const& u )
		: t_( t ), u_( u )
	{
		std::cout << "pair ctor" << std::endl;
	}


//	my_pair_type( T && t, U && u )
//		: t_( std::forward<T>(t) ), u_( std::forward<U>(u) )
//	{
//		std::cout << "pair ctor - move" << std::endl;
//	}

	template<typename T2, typename U2>
	my_pair_type(T2&& t, U2&& u)
		: t_( std::forward<T2>(t) ), u_( std::forward<U2>(u) )
	{
		std::cout << "pair ctor - move - template" << std::endl;
	}

	my_pair_type( my_pair_type const& other )
		: t_(other.t_), u_(other.u_)
	{
		std::cout << "pair copy ctor" << std::endl;
	}

	my_pair_type( my_pair_type && other )
		: t_( std::move(other.t_)), u_( std::move(other.u_))
	{
		std::cout << "pair move ctor" << std::endl;
	}

	~my_pair_type()
	{
		std::cout << "pair dtor" << std::endl;
	}

};




using namespace std;


typedef std::map<std::string, simple_json> map_type;
typedef std::pair<std::string, simple_json> pair_type;
typedef std::pair<std::string, std::string> pair_type_2;
typedef std::pair<std::string, my_simple_class> pair_type_3;
typedef std::pair<std::string, my_vector_type<string> > pair_type_4;

typedef my_pair_type<std::string, my_vector_type<string> > pair_type_5;






void foo( pair_type p )
{

}


void foo_my_simple_class( my_simple_class msc )
{
	std::cout << msc.data_;
}


void foo_pair_ss( my_pair_type<string, string> p )
{
	std::cout << p.t_;
}

void foo_pair_sv( pair_type_5 p )
{
	std::cout << p.t_;
}

void foo_vs( my_vector_type<string> && vs )
{
	std::cout << "my_vector_type<string>" << std::endl;
}

void foo_vs( my_vector_type<string> const& vs )
{
	std::cout << "my_vector_type<string>" << std::endl;
}




int main( /* int argc, char* argv[] */ )
{
//	//string tests...
//	simple_json a("fer");
//	simple_json b = "fer";
//	simple_json c = {"fer"};			//vector or string?
//	simple_json d {"fer"};				//vector or string?
//
//	int x[] = {1, 2, 3};
//	//simple_json e = x;			//Compile time error -> OK
//
//
//	simple_json f = {'a', 'b', 'c'};
//
//	simple_json g = {"fer", "nan", "do"};
//
//	simple_json h = simple_json::map_type{
//										{"name", "fernando"},
//										{"lastname", "pelli"}
//									};
//
//	simple_json i {
//					{"name"_s, "fernando"},
//					{"lastname"_s, "pelli"_s}
//				};


//	{
//		std::vector<my_simple_class> vec;
//		vec.push_back( my_simple_class() );
//
//	}

	{
		//pair_type p = {"list", { "val1", "val2", "val3" } };
		//pair_type_2 p2 = {"list", "val3" };

		//pair_type_3 p3 = {"list", my_simple_class() };

		//my_vector_type<string> vs = { "val1", "val2", "val3" };

		//pair_type_4 p4 = {"list", { "val1", "val2", "val3" } };

		//my_pair_type<string, string> pa1("fer", "nando");
		//my_pair_type<string, string> pa2 = {"fer", "nando"};


		//pair_type_5 p5 = {"list", { "val1", "val2", "val3" } };

		//foo_my_simple_class( my_simple_class() );

		//foo_pair_ss( {"fer", "nando"} );

		//foo_pair_sv( {"list", { "val1", "val2", "val3" } } );




		//		foo_vs( my_vector_type<string>() );
		//		my_vector_type<string> mvs;
		//		foo_vs( mvs );



		//--------

		pair_type_4 p6_b ("list",  { "val1", "val2", "val3" }  );
		//pair_type_4 p7_b ("list", my_vector_type<string>() );


		//pair_type_5 p6 ("list", { "val1", "val2", "val3" } );
		//pair_type_5 p7 ("list", my_vector_type<string>() );


		//std::piecewise_construct,


//		my_vector_type<string> mvs;
//		pair_type_5 p8 ("list", mvs );




	}

	{

//	map_type variables {
//			  {"var"   , "value"}
//			, {"hello" , "Hello World!"}
//			, {"empty" , ""}
//			, {"path"  , "/foo/bar"}
//			, {"x"     , "1024"}
//			, {"y"     , "768"}
//			, {"list"  , { "val1", "val2", "val3" } }
//		};
//		//, {"keys"  , {"key1": "val1", "key2": "val2"}}

	std::cout << "BEGIN FOR" << endl;

//	for (auto& item : variables)
//	{
//		std::cout << item.first << std::endl;
//
//		if ( item.second.get_type() == simple_json::storage_type_enum::string )
//		{
//			std::cout << "string type: ";
//
//			//auto val = get<string>(item.second);	//item.second.template get<string>();
//			//std::cout << "string type: " << val << endl;
//		}
//		//else
//		{
//			std::cout << "other type" << endl;
//		}
//	}


	std::cout << "END FOR" << endl;

	}


	std::cout << "END Program" << endl;

	return 0;
}
