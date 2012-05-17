// clang++ -std=c++11 over.match.list_3.cpp
// clang++ -std=c++11 -stdlib=libc++ over.match.list_3.cpp
// g++ -std=c++11 over.match.list_3.cpp
// g++ -std=c++98 over.match.list_3.cpp

//#include <iostream>
//#include <initializer_list>
#include <string>
#include <utility>

struct Array 
{
	explicit Array(int size);
};

struct Number 
{
	Number(long long);
};

void print(Array);     // (1)
void print(Number);    // (2)

int main( /* int argc, char* argv[] */ )
{
	print(100);				//Not ambigous
	//print({100});		// ambigous

  return 0;
}


/*
[dcl.init]
14 The initialization that occurs in the form
T x = a;
as well as in argument passing, function return, throwing an exception (15.1), handling an exception (15.3),
and aggregate member initialization (8.5.1) is called copy-initialization. [ Note: Copy-initialization may
invoke a move (12.8). —end note ]

*/


/*

13.3.1.7 Initialization by list-initialization [over.match.list]
1 When objects of non-aggregate class type T are list-initialized (8.5.4), overload resolution selects the constructor
in two phases:
— Initially, the candidate functions are the initializer-list constructors (8.5.4) of the class T and the
argument list consists of the initializer list as a single argument.
— If no viable initializer-list constructor is found, overload resolution is performed again, where the
candidate functions are all the constructors of the class T and the argument list consists of the elements
of the initializer list.
If the initializer list has no elements and T has a default constructor, the first phase is omitted. In copy-listinitialization,
if an explicit constructor is chosen, the initialization is ill-formed. [ Note: This differs from
other situations (13.3.1.3, 13.3.1.4), where only converting constructors are considered for copy-initialization.
This restriction only applies if this initialization is part of the final result of overload resolution. —end note ]


*/