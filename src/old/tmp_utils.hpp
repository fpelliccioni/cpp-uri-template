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










//------------------------------------------------------------------------

namespace detail {

template <size_t Index, typename Elem, typename ...Ts>
struct index_of_helper;
//If see an error here. The List doesn't contains the T you are finding.
//{
//typedef typename std::integral_constant<size_t, -1>::type type;
//};


template <size_t Index, typename Elem, typename Current, typename ...Ts>
struct index_of_helper<Index, Elem, Current, Ts...>
{
	typedef typename std::conditional<
		std::is_same<Elem, Current>::value
		, std::integral_constant<size_t, Index>
		, index_of_helper<Index+1, Elem, Ts...>
	>::type temp_type;

	typedef typename temp_type::type type;

	//static constexpr size_t value = type::value;

};

}	//namespace detail

template <typename Elem, typename ...Ts>
struct index_of
{
private:
	typedef typename detail::index_of_helper<0, Elem, Ts...>::type type;
public:
	static constexpr size_t value = type::value;
};

//------------------------------------------------------------------------







#endif // tmp_utils_HPP__
