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
		//std::cout << "ctor 1" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::string;
	}

	simple_json( vector_type&& val )
	{
		//std::cout << "ctor 2" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::vector;
	}

	simple_json( map_type&& val )
	{
		//std::cout << "ctor 3" << std::endl;

		construct(val);
		storage_type_ = storage_type_enum::map;
	}

	template <size_t Size>
	simple_json( const typename string_type::value_type (&array)[Size] )
	{
		//std::cout << "ctor 4" << std::endl;

		construct<string_type>(array);
		storage_type_ = storage_type_enum::string;
	}

	simple_json( std::initializer_list<typename string_type::value_type> init_list )
    {
		//std::cout << "ctor 5" << std::endl;

		construct<string_type>(init_list);
		storage_type_ = storage_type_enum::string;
    }

	simple_json( std::initializer_list<typename vector_type::value_type> init_list )
    {
		//std::cout << "ctor 6" << std::endl;

		construct<vector_type>(init_list);
		storage_type_ = storage_type_enum::vector;
    }

	simple_json( std::initializer_list<typename map_type::value_type> init_list )
    {
		//std::cout << "ctor 7" << std::endl;

		//std::cout << "map: " << std::endl;
//		construct<vector_type>(init_list);
		storage_type_ = storage_type_enum::map;
    }

	simple_json( simple_json const& other )
	{
		switch(other.storage_type_)
		{
			case storage_type_enum::string:
				//std::cout << "copy ctor string" << std::endl;
				construct( *reinterpret_cast<const string_type*>(other.storage_) );
				break;
			case storage_type_enum::vector:
				//std::cout << "copy ctor vec" << std::endl;
				construct( *reinterpret_cast<const vector_type*>(other.storage_) );
				break;
			case storage_type_enum::map:
				//std::cout << "copy ctor map" << std::endl;
				construct( *reinterpret_cast<const map_type*>(other.storage_) );
				break;
			case storage_type_enum::nil:
			default:
				std::cout << "ERROR copy ctor nil" << std::endl;
				break;
		}

		storage_type_ = other.storage_type_;
	}

	simple_json( simple_json && other )
	{
		switch(other.storage_type_)
		{
			case storage_type_enum::string:
				//std::cout << "move ctor string" << std::endl;
				construct( std::move(*reinterpret_cast<string_type*>(other.storage_)) );
				break;
			case storage_type_enum::vector:
				//std::cout << "move ctor vec" << std::endl;
				construct( std::move(*reinterpret_cast<vector_type*>(other.storage_)) );
				break;
			case storage_type_enum::map:
				//std::cout << "move ctor map" << std::endl;
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


	template <typename T, typename Dummy = void>
	struct getter;

	template <typename Dummy>
	struct getter<string_type, Dummy>
	{
		//const string_type & operator()( storage_type_enum storage_type, const char (&storage)[size_] )
		string_type & operator()( storage_type_enum storage_type, char (&storage)[size_] )
		{
			if (storage_type == storage_type_enum::string)
			{
				//return *reinterpret_cast<const string_type*>(storage);
				return *reinterpret_cast<string_type*>(storage);
			}
			else
			{
				throw std::exception();
			}
		}
	};

	template <typename Dummy>
	struct getter<vector_type, Dummy>
	{
		//const string_type & operator()( storage_type_enum storage_type, const char (&storage)[size_] )
		vector_type & operator()( storage_type_enum storage_type, char (&storage)[size_] )
		{
			if (storage_type == storage_type_enum::vector)
			{
				//return *reinterpret_cast<const string_type*>(storage);
				return *reinterpret_cast<vector_type*>(storage);
			}
			else
			{
				throw std::exception();
			}
		}
	};

	template <typename Dummy>
	struct getter<map_type, Dummy>
	{
		map_type & operator()( storage_type_enum storage_type, char (&storage)[size_] )
		{
			if (storage_type == storage_type_enum::map)
			{
				return *reinterpret_cast<map_type*>(storage);
			}
			else
			{
				throw std::exception();
			}
		}
	};


//	template <typename T>
//	const T& get() const


	template <typename T>
	T& get()
	{
		return getter<T>()(storage_type_, storage_);
	}

	~simple_json()
	{
		switch(storage_type_)
		{
			case storage_type_enum::string:
				//std::cout << "destroy string" << std::endl;
				destroy( *reinterpret_cast<string_type*>(storage_) );
				break;
			case storage_type_enum::vector:
				//std::cout << "destroy vec" << std::endl;
				destroy( *reinterpret_cast<vector_type*>(storage_) );
				break;
			case storage_type_enum::map:
				//std::cout << "destroy map" << std::endl;
				destroy( *reinterpret_cast<map_type*>(storage_) );
				break;
			case storage_type_enum::nil:
			default:
				std::cout << "ERROR destroy nil" << std::endl;
				break;
		}
	}

};

template <typename T>
inline T& get( simple_json sj )	//TODO: const?
{
	return sj.get<T>();
}



std::string operator"" _s (const char* p, size_t n)	// std::string literal
{
	std::cout << "std::string operator"" _s (const char* p, size_t n)	// std::string literal" << std::endl;
	return std::string(p, n);	// requires free store allocation
}





using namespace std;


typedef std::map<std::string, simple_json> var_type;


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

	//auto xxx = "fer"_s;

//	auto xxx = {"key1", "val1"};
//	std::cout << typeid(xxx).name() << std::endl;

	auto xxx = {"key1"_s, "val1"_s};
	std::cout << typeid(xxx).name() << std::endl;


	{

		var_type variables {
				  {"var"   , "value"}
				, {"hello" , "Hello World!"}
				, {"empty" , ""}
				, {"path"  , "/foo/bar"}
				, {"x"     , "1024"}
				, {"y"     , "768"}
				, {"list"  , { "val1", "val2", "val3" } }
				, {"keys"  , { {"key1"_s, "val1"}, {"key2", "val2"} } }
			};


		std::cout << "BEGIN FOR" << endl;

		for (auto& item : variables)
		{
			std::cout << item.first << " - ";	//std::endl;

			switch( item.second.get_type() )
			{
				case simple_json::storage_type_enum::string:
				{

					auto val = get<string>(item.second);
					std::cout << "string type: " << val << endl;
				}
					break;
				case simple_json::storage_type_enum::vector:
				{
					std::cout << "vector type: " << endl;

					auto val = get<simple_json::vector_type>(item.second);

					for (auto& vec_item : val)
					{
						std::cout << '\t' << vec_item << std::endl;
					}
				}

					break;
				case simple_json::storage_type_enum::map:
				{
//					std::cout << "map type: " << endl;
//
//					auto val = get<simple_json::map_type>(item.second);
//
//					for (auto& map_item : val)
//					{
//						std::cout << '\t' << map_item.first << ", " << map_item.second << std::endl;
//					}
				}
					break;
				case simple_json::storage_type_enum::nil:
				default:
					std::cout << "uninitialized type" << std::endl;
					break;
			}

//			if ( item.second.get_type() == simple_json::storage_type_enum::string )
//			{
//				auto val = get<string>(item.second);	//item.second.template get<string>();
//				std::cout << "string type: " << val << endl;
//			}
//			else
//			{
//				std::cout << "other type" << endl;
//			}


		}


		std::cout << "END FOR" << endl;

	}


	std::cout << "END Program" << std::endl;

	return 0;
}
