//// g++ -std=c++11 static_string.cpp
//#include <cstdlib>
//#include <cstring>
//#include <iostream>
//
//
//template <size_t Size>
//struct static_string
//{
//	//static constexpr size_t size = Size;
//	static const size_t size = Size;
//
//	char storage_[Size];
//
//	static_string(const char (&data)[Size])
//	{
//		std::memcpy(storage_, data, Size);
//	}
//};
//
////template <size_t Size>
////static_string<Size> make_static_string( const char (&data)[Size] )
//
//template <typename CharT, size_t Size>
//static_string<Size> make_static_string( const CharT (&data)[Size] )
//{
//	std::cout << "lvalue\n";
//	return static_string<Size>(data);
//}
//
//template <typename CharT, size_t Size>
//static_string<Size> make_static_string( CharT (&data)[Size] )
//{
//	std::cout << "rvalue\n";
//	return static_string<Size>(data);
//}
//
//template <typename CharT, size_t Size>
//static_string<Size> make_static_string( CharT (&&data)[Size] )
//{
//	std::cout << "rvalue\n";
//	return static_string<Size>(data);
//}
//
//
////template <size_t SizeL, size_t SizeR>
////static_string<SizeL+SizeR> operator+(static_string<SizeL> str_left, static_string<SizeR> str_right )
////{
////	return static_string<Size+Size2>(data);
////}
//
//
//struct A {};
//
//void foo( const A& a )
//{
//	std::cout << "lvalue\n";
//}
//
//void foo( A&& a )
//{
//	std::cout << "rvalue\n";
//}
//
//int main( /* int argc, char* argv[] */ )
//{
//	//A a;
//	//const A a2;
//
//	//foo(a);
//	//foo(A());
//	//foo(a2);
//
//
//
//	static_string<15> ss("01234567890123");
//
//	//std::cout << ss.size;
//
//	auto xxx = make_static_string("fernando");
//	//std::cout << xxx.size;
//
//	auto xxx_copy = xxx;
//
//
//	char tmp[] = "fer";
//	auto yyy = make_static_string(tmp);
//	//std::cout << yyy.size;
//
//
//	char tmp2[] = {'f', 'e', 'r'};
//	auto zzz = make_static_string(tmp2);
//	//std::cout << zzz.size;
//
//
//	const char tmp3[] = "fer";
//	auto www = make_static_string(tmp3);
//	//std::cout << www.size;
//
//
//	return 0;
//}
