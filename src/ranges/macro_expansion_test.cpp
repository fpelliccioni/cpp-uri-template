// gcc -E cpptest.c
// g++ -E macro_expansion_test.cpp

//clang++ -I$BOOST_ROOT -I$PSTADE_ROOT -std=c++11 -E macro_expansion_test.cpp
//g++ -I$BOOST_ROOT -I$PSTADE_ROOT -std=c++11 -E macro_expansion_test.cpp

//g++ -I"D:/Program Files/Boost/boost_1_49_0/" -I"D:/Program Files/pstade/pstade_1_04_3" -std=c++11 -E macro_expansion_test.cpp
//g++ -I"D:/Program Files/Boost/boost_1_49_0/" -I"D:/Program Files/pstade/pstade_1_04_3" -std=c++11 macro_expansion_test.cpp





//#include <boost/algorithm/string/split.hpp>
//#include <pstade/oven/string_split.hpp>



#include <boost/algorithm/string/split.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/pipable.hpp>



namespace pstade { namespace oven {
namespace string_split_detail {


template< class Range >
struct base
{
	typedef
		boost::algorithm::split_iterator<
		typename range_iterator<Range>::type
		>
		iter_t;

	typedef
		iter_range<iter_t> const
		result_type;

	template< class FinderT >
	result_type operator()(Range& rng, FinderT f) const
	{
		return result_type(iter_t(rng, f), iter_t());
	}
};


} 


namespace adaptor_workarea_of_string_split 
{ 

using namespace boost::mpl::placeholders; 
typedef pstade::egg::deferred<pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) (string_split_detail::base<_>) >::type>::type op; 

} 

typedef adaptor_workarea_of_string_split::op T_make_string_split;

inline void pstade_pod_constant_check_of_make_string_split()
{ 
	pstade::pod_constant_detail::must_be_pod(pstade::unevaluated<pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) (T_make_string_split) >::type&>()); 
} 

pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) (T_make_string_split) >::type const  make_string_split = {{}}; 

inline void pstade_pod_constant_check_of_string_split() 
{ 
	pstade::pod_constant_detail::must_be_pod(pstade::unevaluated<pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) (pstade::egg::result_of_pipable<T_make_string_split>::type) >::type&>());
} 

pstade::unparenthesize_detail::aux< void (::pstade::unparenthesize_detail::klass::*) (pstade::egg::result_of_pipable<T_make_string_split>::type) >::type const  string_split = { { {{}} , {} } };


} } 



int main()
{
	std::string rng("ferna g ndo");
	auto adap = pstade::oven::string_split(boost::first_finder("g", boost::is_iequal()));
	auto xxx = rng|adap;
	
	//pstade::oven::string_split_detail::base<boost::mpl::_> b;



	return 0;
}


//#define SET_FLAGS(w, f) ((w)->flags |= (f))
//
//int main()
//{
//	SET_FLAGS(0, 4711);
//
//	return 0;
//}