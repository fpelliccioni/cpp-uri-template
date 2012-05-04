#ifndef tmp_utils_HPP__
#define tmp_utils_HPP__

// Ver: http://thenewcpp.wordpress.com/2012/02/15/variadic-templates-part-3-or-how-i-wrote-a-variant-class/

// Compile: g++ -std=c++11 main.cpp

#include <type_traits>
//#include <cstdlib>

namespace detail
{

template < template <typename> class Func, typename SoFar, typename... Args >
struct max_helper;


template < template <typename> class Func, typename SoFar >
struct max_helper<Func, SoFar>
{
	static constexpr decltype(Func<SoFar>::value) value = Func<SoFar>::value;
	typedef SoFar type;
};


//---------
template <
	template <typename> class Func,
	typename SoFar, 
	typename Next, 
	typename... Args
>
struct max_helper<Func, SoFar, Next, Args...>
{
private:
	typedef typename std::conditional <
		(Func<Next>::value > Func<SoFar>::value),
		max_helper<Func, Next, Args...>,
		max_helper<Func, SoFar, Args...>
	>::type next_type;

public:
	static constexpr decltype(Func<SoFar>::value) value = next_type::value;

	typedef typename next_type::type type;
};

}	//namespace detail


//---------
template <template <typename> class Func, typename... Args>
struct max;

//---------
template <
	template <typename> class Func, 
	typename First, 
	typename... Args
>
struct max<Func, First, Args...>
{
private:

	typedef decltype(Func<First>::value) size_type;

	typedef detail::max_helper<
		Func, 
		First, 
		Args...
	> helper_type;

public:
	static constexpr size_type value = helper_type::value;
	typedef typename helper_type::type type;
};


#endif // tmp_utils_HPP__
