//// clang++ -std=c++11 variant_test.cpp
//// g++ -std=c++11 variant_test.cpp
//
//#include <iostream>
//#include <list>
//#include <string>
//#include <vector>
//#include <unordered_map>
//
//#include "variant.hpp"
//
//using namespace std;
//
//
//
//
//
//
//
//int main( /* int argc, char* argv[] */ )
//{
//
//	typedef variant<int, double, string> my_variant_1;
//
//	my_variant_1 mv1 ("fer");
//
//	cout << get<string>(mv1) << endl;
//	//cout << get<int>(mv1) << endl;		//run time error
//
//
//
//	typedef variant<int, double, string, vector<int> > my_variant_2;
//
//	my_variant_2 mv2 = "fernando";
//	cout << get<string>(mv2) << endl;
//
//	my_variant_2 mv3 ( { 1, 2, 3, 4, 5, 6, 7 } );
//	auto xxx = get<vector<int>>(mv3);
//
//	for (auto x : xxx)
//	{
//		cout << x << endl;
//	}
//
//	//my_variant_1 mv4 ( { 1, 2, 3, 4, 5, 6, 7 } );		//Compile time error
//	//my_variant_1 mv5 ( { "fer" } );		//Compile time error
//	//my_variant_1 mv6 { "fer" };		//Compile time error
//	//my_variant_1 mv7 = { "fer" };		//Compile time error
//
//
//	return 0;
//}
