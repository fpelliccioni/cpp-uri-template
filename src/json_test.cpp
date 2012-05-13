// clang++ -std=c++11 json_test.cpp
// clang++ -std=c++11 -stdlib=libc++ json_test.cpp
// g++ -std=c++0x json_test.cpp
// g++ -std=c++11 json_test.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>			//#include <unordered_map>


#include "simple_json.hpp"

using namespace std;


typedef std::map<std::string, simple_json> var_type;


int main( /* int argc, char* argv[] */ )
{
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
					std::cout << "map type: " << endl;

					auto val = get<simple_json::map_type>(item.second);

					for (auto& map_item : val)
					{
						std::cout << '\t' << map_item.first << ", " << map_item.second << std::endl;
					}
				}
					break;
				case simple_json::storage_type_enum::nil:
				default:
					std::cout << "uninitialized type" << std::endl;
					break;
			}
		}

		std::cout << "END FOR" << endl;

	}


	std::cout << "END Program" << std::endl;

	return 0;
}
