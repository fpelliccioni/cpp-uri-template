// clang++ -std=c++11 howard_1st_issue.cpp
// clang++ -std=c++11 -stdlib=libc++ howard_1st_issue.cpp
// g++ -std=c++11 howard_1st_issue.cpp

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

template <typename T1, typename T2>
struct my_pair
{
  T1 t1_;
  T2 t2_;

//#ifndef DISABLE_CTOR_1
  my_pair( T1 const& t1, T2 const& t2 )
    : t1_( t1 ), t2_( t2 )
  {
    std::cout << "my_pair ctor" << std::endl;
  }
//#endif

  template<typename U1, typename U2>
  my_pair( U1&& u1, U2&& u2 )
    : t1_( std::forward<U1>(u1) ), t2_( std::forward<U2>(u2) )
  {
    std::cout << "my_pair ctor - && - template" << std::endl;
  }

  my_pair( my_pair const& other )
    : t1_(other.t1_), t2_(other.t2_)
  {
    std::cout << "my_pair copy ctor" << std::endl;
  }

  my_pair( my_pair && other )
    : t1_( std::move(other.t1_)), t2_( std::move(other.t2_))
  {
    std::cout << "my_pair move ctor" << std::endl;
  }

  ~my_pair()
  {
    std::cout << "my_pair dtor" << std::endl;
  }
  
  
#ifdef MY_PAIR_NEW_CTOR
  my_pair( T1 && t1, T2 && t2 )
    : t1_( std::forward<T1>(t1) ), t2_( std::forward<T2>(t2) )
  {
    std::cout << "my_pair ctor - &&" << std::endl;
  }
#endif




  

  //Not used
  template < typename U1, typename U2 >
  my_pair( const my_pair<U1,U2>& p );

  template < typename U1, typename U2 >
  my_pair( my_pair<U1,U2>&& p );

};


using namespace std;


typedef std::pair<std::string, my_vector<string> > std_pair_type;
typedef my_pair<std::string, my_vector<string> > my_pair_type;

int main( /* int argc, char* argv[] */ )
{
  std_pair_type p1 ("list", my_vector<string>() );
  cout << "-------------------------------------\n";
  std_pair_type p2 ("list",  { "val1", "val2", "val3" }  );
  cout << "-------------------------------------\n";


  
  
  my_pair_type p3 ("list", my_vector<string>() );
  cout << "-------------------------------------\n";
  my_pair_type p4 ("list", { "val1", "val2", "val3" } );
  cout << "-------------------------------------\n";



  return 0;
}
