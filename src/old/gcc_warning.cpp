//#include <string>
//
//void foo( std::string && str ) {}
//
//int main( /* int argc, char* argv[] */ )
//{
//	foo( "k0" );
//
//	return 0;
//}


#include <string>
#include <utility>

//void foo( std::string ) {}
void foo( std::pair<std::string, std::string> ) {}

int main( /* int argc, char* argv[] */ )
{
	foo( {"k0", "v0"} );

  return 0;
}
