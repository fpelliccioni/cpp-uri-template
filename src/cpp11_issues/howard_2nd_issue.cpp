// clang++ -std=c++11 howard_2nd_issue.cpp
// clang++ -std=c++11 -stdlib=libc++ howard_2nd_issue.cpp
// g++ -std=c++11 howard_2nd_issue.cpp
// g++ -std=c++98 howard_2nd_issue.cpp

//#include <iostream>
#include <string>
#include <utility>


void foo( std::string );
//{}

void foo( std::pair<std::string, std::string> );
//{}

int main( /* int argc, char* argv[] */ )
{
	foo( {"k0", "v0"} );


  return 0;
}
