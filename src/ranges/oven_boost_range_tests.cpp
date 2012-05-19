// $(BOOST_ROOT);$(PSTADE_ROOT);D:\Program Files\pstade\pstade_1_04_3



#include <iostream>
//#include <string>
//#include <vector>
#include <typeinfo>


#include <boost/range/join.hpp>
#include <boost/range/iterator_range.hpp>
////#include <boost/range/adaptors.hpp>
//#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/reversed.hpp>
//#include <boost/range/irange.hpp>
#include <boost/range/algorithm/copy.hpp>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find_iterator.hpp>

#include <pstade/oven/string_split.hpp>
#include <pstade/oven/upper_chars.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/as_literal.hpp>



struct my_range : boost::iterator_range<char*>
{
	typedef boost::iterator_range<char*> base;

	////template <typename CharT, size_t Size>
	//template <size_t Size>
	//my_range( char (&data)[Size] )
	//	: base(data)
	//{
	//}

	//template <typename CharT, size_t Size>
	template <size_t Size>
	my_range( char (&data)[Size] )
		: base(std::begin(data), std::end(data))
	{
	}

};

//TODO: Crear un boost::range::joined_range que "diga" la informacion de sus template parameters

template <typename SinglePassRange1, typename SinglePassRange2>
boost::range::joined_range<SinglePassRange1, SinglePassRange2>
	operator+(SinglePassRange1& r1, SinglePassRange2& r2)
{
	//TODO: check recursively if SinglePassRange1 is related only with my_range and joined_range
	//TODO: check recursively if SinglePassRange2 is related only with my_range and joined_range

	//BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
	//BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

	return boost::range::join(r1, r2);
}

// operator<<
// 

//TODO: ver esta funcion...
template<typename RangeT>
inline boost::split_iterator< 
	BOOST_STRING_TYPENAME boost::range_iterator<RangeT>::type>
make_split_iterator_end(RangeT& Collection)
{
	return boost::split_iterator<BOOST_STRING_TYPENAME boost::range_iterator<RangeT>::type>();
}



int main( /* int argc, char* argv[] */ )
{
	//using boost::adaptors::reversed;
	//using boost::copy;
	using boost::range::join;
	//using boost::irange;



	//////std::vector<int> vi = {1, 2, 3};
	////int tmp_vi[]  = {1, 2, 3};
	////std::vector<int> vi(tmp_vi, tmp_vi+3);
	////copy( vi, std::ostream_iterator<int>(std::cout) );
	////copy( vi | reversed, std::ostream_iterator<int>(std::cout) );


	typedef boost::iterator_range<const char*> my_str;


	char tmp[] = "c++";
	char tmp2[] = "string";
	char tmp3[] = "range";
	char tmp4[] = "test";

	//my_str ms(tmp);
	//my_str ms2(tmp2);
	////my_str ms("fernando");
	////std::cout << ms.size() << std::endl;
	////copy( ms, std::ostream_iterator<char>(std::cout) );
	////copy( ms | reversed, std::ostream_iterator<char>(std::cout) );


	////std::string str("fernando");
	////std::cout << str << std::endl;

	my_range mr(tmp);
	//copy( mr, std::ostream_iterator<char>(std::cout) );
	//copy( mr | reversed, std::ostream_iterator<char>(std::cout) );
	//
	////auto it = std::begin(mr);
	////auto end = std::end(mr);

	////for ( ; it != end; ++it )
	////{
	////	std::cout << *it << std::endl;
	////}


	my_range mr2(tmp2);
	my_range mr3(tmp3);
	my_range mr4(tmp4);

	//------------------------------------------------------------------------------------------------
	// Join / Concat


	copy( mr + mr2, std::ostream_iterator<char>(std::cout) );
	std::cout << std::endl;
	copy( mr + mr2 + mr3 + mr4 + mr, std::ostream_iterator<char>(std::cout) );
	std::cout << std::endl;

	auto jr8 = mr + mr2;

	//typedef boost::range::joined_range<my_range, my_range> joined_type;

	//typedef joined_type::iterator::iterator1_t xxx;
	//typedef joined_type::iterator::iterator2_t xxx2;

	//std::cout << typeid(xxx).name() << std::endl;
	//std::cout << typeid(xxx2).name() << std::endl;


	auto jr9 = mr + mr2 + "a ver";
	copy( jr9, std::ostream_iterator<char>(std::cout) );
	std::cout << std::endl;


	//------------------------------------------------------------------------------------------------



	//------------------------------------------------------------------------------------------------
	// range-based for loop

	//for ( auto& x : jr9 )
	//{
	//	std::cout << x << std::endl;
	//}


	//------------------------------------------------------------------------------------------------



	//------------------------------------------------------------------------------------------------
	// Random Access

	std::cout << mr2[0] << std::endl;
	std::cout << jr9[0] << std::endl;
	std::cout << jr9[13] << std::endl;

	//------------------------------------------------------------------------------------------------



	//------------------------------------------------------------------------------------------------
	// Split

	//TODO: ver si existe un Split Range en Boost.Range o en Oven
	//TODO: ver subrange
	//TODO: sino existe... crear uno...

	{
		typedef boost::split_iterator<char*> char_array_split_iterator;

		auto end = make_split_iterator_end(jr9);
		auto it = boost::make_split_iterator(jr9, boost::first_finder(" ", boost::is_iequal()));

		for ( ; it != end; ++it )
		{
			std::cout << boost::copy_range<std::string>(*it) << std::endl;
		}

	}


	{
		auto aver = jr9|pstade::oven::string_split(boost::first_finder("g", boost::is_iequal()));
		//copy( aver, std::ostream_iterator<char>(std::cout) );

		auto it = std::begin(aver);
		auto end = std::end(aver);

		for ( ; it != end; ++it )
		{
			std::cout << boost::copy_range<std::string>(*it) << std::endl;
		}

	}




	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	// Upper / Lower

	{
		my_range rng1(tmp3);

		auto res = rng1|pstade::oven::upper_chars;

		copy( res, std::ostream_iterator<char>(std::cout) );
	}
	//------------------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------------------------
	// as_c_str and as_literal

	{
		auto rng = pstade::oven::as_c_str("fernando");						//strlen
		copy( rng, std::ostream_iterator<const char>(std::cout) );


		auto rng2 = pstade::oven::as_literal("fernando");	 				//compile-time (template) Size
		copy( rng2, std::ostream_iterator<const char>(std::cout) );

	}
	//------------------------------------------------------------------------------------------------


	//Importantes: ver single (de pstade)
	




	return 0;
}

