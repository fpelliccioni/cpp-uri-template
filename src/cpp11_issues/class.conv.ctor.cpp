// clang++ -std=c++11 class.conv.ctor.cpp
// clang++ -std=c++11 -stdlib=libc++ class.conv.ctor.cpp
// g++ -std=c++11 class.conv.ctor.cpp
// g++ -std=c++98 class.conv.ctor.cpp

//#include <iostream>
#include <initializer_list>
#include <string>
#include <utility>

struct my_type
{
	my_type( std::initializer_list<int> il );
	my_type( std::initializer_list<double> il );
		
	my_type( int i1, int i2 );
	my_type( double d1, double d2 );
	my_type( char c1, char c2 );
	
};


int main( /* int argc, char* argv[] */ )
{
	
	//my_type mt1 = {1, 2};			//copy-list-initialization
	//my_type mt2 {1, 2};
	my_type mt3 {1.0, 2.0};
	//my_type mt3 {'a', 'b'};

  return 0;
}




////#include <iostream>
//#include <string>
//#include <utility>
//
//struct like_std_string
//{
//  template<class InputIterator>
//  like_std_string(InputIterator begin, InputIterator end);      // This is a converting constructor.
//};
//
//struct my_string
//{
//  template<class InputIterator>
//  explicit my_string(InputIterator begin, InputIterator end);   // This is *not* a converting constructor.
//};
//
//void foo( like_std_string ); //{}
//void foo( std::pair<std::string, std::string> ); //{}
//
//void bar( my_string ); //{}
//void bar( std::pair<std::string, std::string> ); //{}
//
//int main( /* int argc, char* argv[] */ )
//{
//  foo( {"k0", "v0"} );	//ambiguous
//  bar( {"k0", "v0"} );	// *not* ambiguous, I think!
//
//  return 0;
//}





// ------ Issue -> Poner ejemplos con dos o más parametros (no-default)
// C++11
/*

12.3.1 Conversion by constructor [class.conv.ctor]
1 A constructor declared without the function-specifier explicit specifies a conversion from the types of its
parameters to the type of its class. Such a constructor is called a converting constructor. [ Example:
struct X {
X(int);
X(const char*, int =0);
};
void f(X arg) {
X a = 1; // a = X(1)
X b = "Jessie"; // b = X("Jessie",0)
a = 2; // a = X(2)
f(3); // f(X(3))
}
—end example ]

*/


// C++03
/*
12.3.1 Conversion by constructor [class.conv.ctor]
1 A constructor declared without the function-specifier explicit that can be called with a single parameter
specifies a conversion from the type of its first parameter to the type of its class. Such a constructor is
called a converting constructor. [Example:
class X {
// ...
public:
X(int);
X(const char*, int =0);
};
193
ISO/IEC 14882:2003(E) ? ISO/IEC
12.3.1 Conversion by constructor 12 Special member functions
void f(X arg)
{
X a = 1; // a = X(1)
X b = "Jessie"; // b = X("Jessie",0)
a = 2; // a = X(2)
f(3); // f(X(3))
}
—end example]
2

*/