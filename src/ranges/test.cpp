// g++     -I"D:\Program Files\Boost\boost_1_49_0" -std=c++11 test.cpp
// clang++ -I$BOOST_ROOT -std=c++11 test.cpp
// clang++ -I$BOOST_ROOT -std=c++11 -stdlib=libc++ test.cpp				--runtime error

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

//#include <boost/algorithm/string/find_iterator.hpp>	//boost::split_iterator
//#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/classification.hpp>
#include <boost/optional.hpp>



struct str_range
{
	char* begin_;		//TODO: type independent
	char* end_;

	str_range( char* begin, char* end )
		: begin_(begin), end_(end)
	{
	}
};

template <typename T, size_t Size>
str_range make_range( T (&array)[Size] )		//const T (&array)[Size]
{
	return str_range( std::begin(array), std::end(array) );
}








//const char* operators = "+./;?|!@";
const char operators[] = "+./;?|!@";

template <typename T, size_t Size>
const T* find( const T (&array)[Size],  T const& value )
{
	return std::find( std::begin(array), std::end(array), value );
}

//TODO: use compile time metafunction
inline bool is_operator( char chr )
{
	auto it = find(operators, chr);
	return (it != std::end(operators));
}



//TODO: see if could be optimized using a Range for safe paramter
std::string escape( std::string const& text, std::string const& safe = "" )
{
	std::stringstream ss;

	for ( auto chr : text )
	{
		if ((chr == 0x2D) || (chr == 0x2E) || //(chr == 0x2F) || // Hyphen-Minus, Full Stop, Slash¿?
		   ((0x30 <= chr) && (chr <= 0x39)) || // Digits [0-9]
		   ((0x41 <= chr) && (chr <= 0x5A)) || // Uppercase [A-Z]
		   ((0x61 <= chr) && (chr <= 0x7A)))   // Lowercase [a-z]
		{
			ss << chr;
		}
		else
		{
			if ( safe.size() != 0 )
			{
				auto it = std::find( std::begin(safe), std::end(safe), chr);
				if (it != std::end(safe))
				{
					ss << chr;
				}
				else
				{
					ss << '%';
					ss << std::setw(2) << std::setfill( '0' ) << std::hex << std::uppercase << static_cast<unsigned short>(chr);
				}
			}
			else
			{
				ss << '%';
				//ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned short>(chr);
				ss << std::setw(2) << std::setfill( '0' ) << std::hex << std::uppercase << static_cast<unsigned short>(chr);
			}
		}
	}

	return ss.str();	//TODO: verify copy elision ...
}


template <typename Map>
boost::optional<typename Map::mapped_type> get_map_item( Map const& map, typename Map::key_type const& key )
{
	typename Map::const_iterator it = map.find(key);

	if ( it != map.end() )
	{
		return boost::optional<typename Map::mapped_type>(it->second);
	}
	else
	{
		return boost::optional<typename Map::mapped_type>();
	}
}



void substr_string_test( std::string const& text )
{
	std::string variable_name = "";

	char op = 0;

	if ( is_operator( text[0] ) )
	{
		op = text[0];
		variable_name = text.substr(1, text.size()-1);		//TODO: i dont want to copy the string
	}
	else
	{
		variable_name = text;								//TODO: i dont want to copy the string
	}

	std::cout << variable_name << std::endl;
}

void substr_range_test( std::string const& text )
{
	std::string variable_name = "";

	char op = 0;

	if ( is_operator( text[0] ) )
	{
		op = text[0];
		variable_name = text.substr(1, text.size()-1);		//TODO: i dont want to copy the string
	}
	else
	{
		variable_name = text;								//TODO: i dont want to copy the string
	}

	std::cout << variable_name << std::endl;
}




//------------------------------------------------------------------------

int main( /* int argc, char* argv[] */ )
{
	//for ( auto item : testcases )
	//{
	//	test(item.first, item.second);
	//}


	//substr_string_test("+fernando");
	//substr_range_test("+fernando");


	char temp[] = "+fernando";
	std::cout << temp << std::endl;

	str_range rng = make_range(temp);
	std::cout << rng << std::endl;


	return 0;
}
