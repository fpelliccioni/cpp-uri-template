//// g++     -I"D:\Program Files\Boost\boost_1_49_0" -std=c++11 test.cpp
//// clang++ -I$BOOST_ROOT -std=c++11 test.cpp
//// clang++ -I$BOOST_ROOT -std=c++11 -stdlib=libc++ test.cpp				--runtime error
//
//
//// http://tools.ietf.org/html/rfc6570
//// http://code.google.com/p/uri-templates/source/browse/trunk/testdata.json
//
//// Eliminado -- Compiler optimization flags: -emit-llvm
//// Eliminado -- Compiler other flags: -c
//
///*
//
//${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT}
//
//clang++ -I/home/fernando/software/boost/boost_1_49_0 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o src/test.bc ../src/test.cpp
//llvm-ld -v -L/usr/lib/gcc/i686-linux-gnu/4.6/ -o cpp-uri-template src/test.bc -lstdc++
//
//
// */
//
//#include <array>
//#include <algorithm>
//#include <iostream>
//#include <string>
//#include <unordered_map>
//#include <vector>
//
//#include <boost/algorithm/string/find_iterator.hpp>	//boost::split_iterator
//#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/classification.hpp>
//#include <boost/optional.hpp>
//#include <boost/variant.hpp>
//#include <boost/xpressive/xpressive.hpp>
//
//#include <boost/spirit/include/support_utree.hpp>
//
//
////#include "uri_template.hpp"
//
//using namespace boost::xpressive;
//
//#ifndef _MSC_VER
////using strmap = std::unordered_map<std::string, std::string>;
//using strmap = std::map<std::string, std::string>;
//#else
//typedef std::map<std::string, std::string> strmap;
//#endif
//
//strmap variables;
//strmap testcases;
//
//sregex re = as_xpr('{') >> (s1= +(~(set= '}'))) >> '}';
//
////const char* operators = "+./;?|!@";
//const char operators[] = "+./;?|!@";
//
//int ok_results = 0;
//int error_results = 0;
//
//void initialize()
//{
//#ifndef _MSC_VER
//
//	variables = {
//		  {"var"   , "value"}
//		, {"hello" , "Hello World!"}
//		, {"empty" , ""}
//		, {"path"  , "/foo/bar"}
//		, {"x"     , "1024"}
//		, {"y"     , "768"}
//	};
//	//, {"list"  , [ "val1", "val2", "val3" ]}
//	//, {"keys"  , {"key1": "val1", "key2": "val2"}}
//
//
//	testcases = {
//		{"{var}", "value"}
//		, {"{hello}", "Hello%20World%21"}
//		, {"{path}/here", "%2Ffoo%2Fbar/here"}
//		, {"{x,y}", "1024,768"}
//		, {"{var=default}", "value"}
//		, {"{undef=default}", "default"}
//		//, {"{list}", "val1,val2,val3"}
//		//, {"{list*}", "val1,val2,val3"}
//		//, {"{list+}", "list.val1,list.val2,list.val3"}
//		//, {"{keys}", "key1,val1,key2,val2"}
//		//, {"{keys*}", "key1,val1,key2,val2"}
//		//, {"{keys+}", "keys.key1,val1,keys.key2,val2"}
//		, {"{+var}", "value"}
//		, {"{+hello}", "Hello%20World!"}
//		, {"{+path}/here", "/foo/bar/here"}
//		, {"{+path,x}/here", "/foo/bar,1024/here"}
//		, {"{+path}{x}/here", "/foo/bar1024/here"}
//		, {"{+empty}/here", "/here"}
//		, {"{+undef}/here", "/here"}
//		//, {"{+list}", "val1,val2,val3"}
//		//, {"{+list*}", "val1,val2,val3"}
//		//, {"{+list+}", "list.val1,list.val2,list.val3"}
//		//, {"{+keys}", "key1,val1,key2,val2"}
//		//, {"{+keys*}", "key1,val1,key2,val2"}
//		//, {"{+keys+}", "keys.key1,val1,keys.key2,val2"}
//		, {"{;x,y}", ";x=1024;y=768"}
//		, {"{;x,y,empty}", ";x=1024;y=768;empty"}
//		, {"{;x,y,undef}", ";x=1024;y=768"}
//		//, {"{;list}", ";val1,val2,val3"}
//		//, {"{;list*}", ";val1;val2;val3"}
//		//, {"{;list+}", ";list=val1;list=val2;list=val3"}
//		//, {"{;keys}", ";key1,val1,key2,val2"}
//		//, {"{;keys*}", ";key1=val1;key2=val2"}
//		//, {"{;keys+}", ";keys.key1=val1;keys.key2=val2"}
//		, {"{?x,y}", "?x=1024&y=768"}
//		, {"{?x,y,empty}", "?x=1024&y=768&empty"}
//		, {"{?x,y,undef}", "?x=1024&y=768"}
//		//, {"{?list}", "?list=val1,val2,val3"}
//		//, {"{?list*}", "?val1&val2&val3"}
//		//, {"{?list+}", "?list=val1&list=val2&list=val3"}
//		//, {"{?keys}", "?keys=key1,val1,key2,val2"}
//		//, {"{?keys*}", "?key1=val1&key2=val2"}
//		//, {"{?keys+}", "?keys.key1=val1&keys.key2=val2"}
//		, {"{/var}", "/value"}
//		, {"{/var,empty}", "/value/"}
//		, {"{/var,undef}", "/value"}
//		//, {"{/list}", "/val1,val2,val3"}
//		//, {"{/list*}", "/val1/val2/val3"}
//		//, {"{/list*,x}", "/val1/val2/val3/1024"}
//		//, {"{/list+}", "/list.val1/list.val2/list.val3"}
//		//, {"{/keys}", "/key1,val1,key2,val2"}
//		//, {"{/keys*}", "/key1/val1/key2/val2"}
//		//, {"{/keys+}", "/keys.key1/val1/keys.key2/val2"}
//		, {"X{.var}", "X.value"}
//		, {"X{.empty}", "X"}
//		, {"X{.undef}", "X"}
//		//, {"X{.list}", "X.val1,val2,val3"}
//		//, {"X{.list*}", "X.val1.val2.val3"}
//		//, {"X{.list*,x}", "X.val1.val2.val3.1024"}
//		//, {"X{.list+}", "X.list.val1.list.val2.list.val3"}
//		//, {"X{.keys}", "X.key1,val1,key2,val2"}
//		//, {"X{.keys*}", "X.key1.val1.key2.val2"}
//		//, {"X{.keys+}", "X.keys.key1.val1.keys.key2.val2"}
//	};
//
//
//#else
//	variables["var"] = "value";
//	variables["hello"] = "Hello World!";
//	variables["empty"] = "";
//	variables["path"] = "/foo/bar";
//	variables["x"] = "1024";
//	variables["y"] = "768";
//	//, {"list"  , [ "val1", "val2", "val3" ]}
//	//, {"keys"  , {"key1": "val1", "key2": "val2"}}
//
//
//	testcases["{var}"] = "value";
//	testcases["{hello}"] = "Hello%20World%21";
//	testcases["{path}/here"] = "%2Ffoo%2Fbar/here";
//	testcases["{x,y}"] = "1024,768";
//	testcases["{var=default}"] = "value";
//	testcases["{undef=default}"] = "default";
//	//testcases["{list}"] = "val1,val2,val3";
//	//testcases["{list*}"] = "val1,val2,val3";
//	//testcases["{list+}"] = "list.val1,list.val2,list.val3";
//	//testcases["{keys}"] = "key1,val1,key2,val2";
//	//testcases["{keys*}"] = "key1,val1,key2,val2";
//	//testcases["{keys+}"] = "keys.key1,val1,keys.key2,val2";
//	testcases["{+var}"] = "value";
//	testcases["{+hello}"] = "Hello%20World!";
//	testcases["{+path}/here"] = "/foo/bar/here";
//	testcases["{+path,x}/here"] = "/foo/bar,1024/here";
//	testcases["{+path}{x}/here"] = "/foo/bar1024/here";
//	testcases["{+empty}/here"] = "/here";
//	testcases["{+undef}/here"] = "/here";
//	//testcases["{+list}"] = "val1,val2,val3";
//	//testcases["{+list*}"] = "val1,val2,val3";
//	//testcases["{+list+}"] = "list.val1,list.val2,list.val3";
//	//testcases["{+keys}"] = "key1,val1,key2,val2";
//	//testcases["{+keys*}"] = "key1,val1,key2,val2";
//	//testcases["{+keys+}"] = "keys.key1,val1,keys.key2,val2";
//	testcases["{;x,y}"] = ";x=1024;y=768";
//	testcases["{;x,y,empty}"] = ";x=1024;y=768;empty";
//	testcases["{;x,y,undef}"] = ";x=1024;y=768";
//	//testcases["{;list}"] = ";val1,val2,val3";
//	//testcases["{;list*}"] = ";val1;val2;val3";
//	//testcases["{;list+}"] = ";list=val1;list=val2;list=val3";
//	//testcases["{;keys}"] = ";key1,val1,key2,val2";
//	//testcases["{;keys*}"] = ";key1=val1;key2=val2";
//	//testcases["{;keys+}"] = ";keys.key1=val1;keys.key2=val2";
//	testcases["{?x,y}"] = "?x=1024&y=768";
//	testcases["{?x,y,empty}"] = "?x=1024&y=768&empty";
//	testcases["{?x,y,undef}"] = "?x=1024&y=768";
//	//testcases["{?list}"] = "?list=val1,val2,val3";
//	//testcases["{?list*}"] = "?val1&val2&val3";
//	//testcases["{?list+}"] = "?list=val1&list=val2&list=val3";
//	//testcases["{?keys}"] = "?keys=key1,val1,key2,val2";
//	//testcases["{?keys*}"] = "?key1=val1&key2=val2";
//	//testcases["{?keys+}"] = "?keys.key1=val1&keys.key2=val2";
//	testcases["{/var}"] = "/value";
//	testcases["{/var,empty}"] = "/value/";
//	testcases["{/var,undef}"] = "/value";
//	//testcases["{/list}"] = "/val1,val2,val3";
//	//testcases["{/list*}"] = "/val1/val2/val3";
//	//testcases["{/list*,x}"] = "/val1/val2/val3/1024";
//	//testcases["{/list+}"] = "/list.val1/list.val2/list.val3";
//	//testcases["{/keys}"] = "/key1,val1,key2,val2";
//	//testcases["{/keys*}"] = "/key1/val1/key2/val2";
//	//testcases["{/keys+}"] = "/keys.key1/val1/keys.key2/val2";
//	testcases["X{.var}"] = "X.value";
//	testcases["X{.empty}"] = "X";
//	testcases["X{.undef}"] = "X";
//	//testcases["X{.list}"] = "X.val1,val2,val3";
//	//testcases["X{.list*}"] = "X.val1.val2.val3";
//	//testcases["X{.list*,x}"] = "X.val1.val2.val3.1024";
//	//testcases["X{.list+}"] = "X.list.val1.list.val2.list.val3";
//	//testcases["X{.keys}"] = "X.key1,val1,key2,val2";
//	//testcases["X{.keys*}"] = "X.key1.val1.key2.val2";
//	//testcases["X{.keys+}"] = "X.keys.key1.val1.keys.key2.val2";
//
//#endif
//}
//
//
//
//template <typename T, size_t Size>
//const T* find( const T (&array)[Size],  T const& value )
//{
//	return std::find( std::begin(array), std::end(array), value );
//}
//
////TODO: use compile time metafunction
//inline bool is_operator( char chr )
//{
//	auto it = find(operators, chr);
//	return (it != std::end(operators));
//}
//
//
//
////TODO: see if could be optimized using a Range for safe paramter
//std::string escape( std::string const& text, std::string const& safe = "" )
//{
//	std::stringstream ss;
//
//	for ( auto chr : text )
//	{
//		if ((chr == 0x2D) || (chr == 0x2E) || //(chr == 0x2F) || // Hyphen-Minus, Full Stop, Slash¿?
//		   ((0x30 <= chr) && (chr <= 0x39)) || // Digits [0-9]
//		   ((0x41 <= chr) && (chr <= 0x5A)) || // Uppercase [A-Z]
//		   ((0x61 <= chr) && (chr <= 0x7A)))   // Lowercase [a-z]
//		{
//			ss << chr;
//		}
//		else
//		{
//			if ( safe.size() != 0 )
//			{
//				auto it = std::find( std::begin(safe), std::end(safe), chr);
//				if (it != std::end(safe))
//				{
//					ss << chr;
//				}
//				else
//				{
//					ss << '%';
//					ss << std::setw(2) << std::setfill( '0' ) << std::hex << std::uppercase << static_cast<unsigned short>(chr);
//				}
//			}
//			else
//			{
//				ss << '%';
//				//ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned short>(chr);
//				ss << std::setw(2) << std::setfill( '0' ) << std::hex << std::uppercase << static_cast<unsigned short>(chr);
//			}
//		}
//	}
//
//	return ss.str();	//TODO: verify copy elision ...
//}
//
//
//template <typename Map>
//boost::optional<typename Map::mapped_type> get_map_item( Map const& map, typename Map::key_type const& key )
//{
//	typename Map::const_iterator it = map.find(key);
//
//	if ( it != map.end() )
//	{
//		return boost::optional<typename Map::mapped_type>(it->second);
//	}
//	else
//	{
//		return boost::optional<typename Map::mapped_type>();
//	}
//}
//
//
//
//
//
//
////TODO: naive function for test only... need refactor (code clean & performance)
//
//std::string format_fun( smatch const& what )
//{
//	auto text = what[1].str();
//	std::string variable_name = "";			//TODO: rename variable_name
//
//	char op = 0;
//
//	if ( is_operator( text[0] ) )
//	{
//		op = text[0];
//		variable_name = text.substr(1, text.size()-1);		//TODO: i dont want to copy the string
//		//std::cout << variable_name << std::endl;
//	}
//	else
//	{
//		variable_name = text;								//TODO: i dont want to copy the string
//	}
//
//	std::string safe = "";		//TODO: no usar string, usar un char array
//	if ( op == '+' )
//	{
//		safe = ":/?#[]@!$&'()*+,;=";
//	}
//
//
//	//TODO: hacer Split de variable_name por comma ',' e ir concatenando los resultados
//
//	std::string result;		//TODO: ver de reemplazar por un stringstream
//
//
//    typedef boost::split_iterator<std::string::iterator> string_split_iterator;
//
//    string_split_iterator it = boost::make_split_iterator(variable_name, boost::first_finder(",", boost::is_iequal()));
//    string_split_iterator end;
//    bool first = true;
//
//    for ( ; it != end; ++it )
//    {
//        std::string data = boost::copy_range<std::string>(*it);	//TODO: ver
//
//    	//typedef std::vector<std::string> vector_type;
//    	typedef std::vector< boost::iterator_range<std::string::iterator> > vector_type;
//
//    	vector_type SplitVec;
//    	boost::split( SplitVec, data, boost::is_any_of("="), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
//
//
//
//
//    	std::string key = boost::copy_range<std::string>(SplitVec[0]);		//TODO: feo
//    	std::string default_value;
//    	if ( SplitVec.size() == 2 )
//    	{
//    		default_value = boost::copy_range<std::string>(SplitVec[1]);		//TODO: feo
//    	}
//
//
//
//        auto item = get_map_item(variables, key);		//TODO: ver si puedo usar rangos o vistas (de strings) para buscar en el Map
//
//        if (item)
//        {
//        	std::string var_value = *item;
//
//
//
//			var_value = escape(var_value, safe);
//
//			if ( op == 0 && ! first )
//			{
//				//if ( var_value != "" )		//TODO: verificar {empty,empty,empty}
//				//{
//					result += ',';
//				//}
//			}
//
//			if ( op == '+' && ! first )
//			{
//				//if ( var_value != "" )		//TODO: verificar {empty,empty,empty}
//				//{
//					result += ',';
//				//}
//			}
//
//			if ( op == '/' && ! first )
//			{
//				//if ( var_value != "" )		//TODO: verificar {empty,empty,empty}
//				//{
//					result += '/';
//				//}
//			}
//
//			if ( op == ';' )
//			{
//				if ( ! first )
//				{
//					result += ';';
//				}
//
//				result += key;
//				if ( var_value != "" )
//				{
//					result += '=';
//				}
//			}
//
//			if ( op == '?' )
//			{
//				if ( ! first )
//				{
//					result += '&';
//				}
//
//				result += key;
//				if ( var_value != "" )
//				{
//					result += '=';
//				}
//			}
//
//			first = false;
//
//			result += var_value;
//        }
//        else
//        {
//        	if ( ! default_value.empty() )
//        	{
//        		result += default_value;
//        	}
//        }
//    }
//
//
//
//	if ( op == '.' )
//	{
//		if ( result != "" )
//		{
//			result = op + result;	//TODO: copy
//		}
//	}
//
//	if ( op == '/' )
//	{
//		if ( result != "" )
//		{
//			result = op + result;	//TODO: copy
//		}
//	}
//
//	if ( op == ';' )
//	{
//		if ( result != "" )
//		{
//			result = op + result;	//TODO: copy
//		}
//	}
//
//	if ( op == '?' )
//	{
//		if ( result != "" )
//		{
//			result = op + result;	//TODO: copy
//		}
//	}
//
//	// std::cout << result << std::endl;
//	return result;
//}
//
//
//void test( std::string const& uritemplate, std::string const& expected )
//{
//	std::string output = regex_replace(uritemplate, re, format_fun);
//
//	if (output != expected)
//	{
//		std::cout << "ERROR \t\t template: " << uritemplate << "\t\texpected: " << expected << "\t\tresult: " << output << std::endl;
//		error_results++;
//	}
//	else
//	{
//		std::cout << "OK \t\t template: " << uritemplate << "\t\texpected: " << expected << "\t\tresult: " << output << std::endl;
//		ok_results++;
//	}
//}
//
////------------------------------------------------------------------------
//
//template <typename T1, typename T2>
//struct my_variant_type
//{
//	template <typename T>
//	my_variant_type( T const& t )
//	{
//		std::cout << typeid(t).name() << std::endl;
//	}
//
//	template <typename T>
//	my_variant_type( std::initializer_list<T> const& t )
//	{
//		std::cout << typeid(t).name() << std::endl;
//	}
//};
//
//
////------------------------------------------------------------------------
//
//template <typename ...Ts>
//struct other_variant {};
//
//template <typename T, typename ...Ts>
//struct other_variant<T, Ts...> : other_variant<Ts...> //private other_variant<Ts...>
//{
//	typedef other_variant<Ts...> base;
//
////private:
//	//T head_;
//
//	union U
//	{
//		T e;
//	} u;
//};
//
////------------------------------------------------------------------------
//
//int main( /* int argc, char* argv[] */ )
//{
////	//typedef boost::variant<std::string, std::vector<std::string>> variant_type;
////	typedef boost::variant<std::string, std::initializer_list<std::string>> variant_type;
////	using strmap_temp = std::map<std::string, variant_type>;
////
////	//, {"key3", {"val1", "val2", "val3"} }
////
////	strmap_temp my_map = {
////			  {"key1", "value1"}
////			, {"key2", "value2"}
////	};
////
////	variant_type vt = "val";
////	variant_type vt2 = { "val", "val2" };
////	auto xxx = { "val", "val2" };
////
////	std::cout << typeid(xxx).name() << std::endl;
////
////	std::initializer_list<std::string> is;
//
//
//	typedef my_variant_type<std::string, std::vector<std::string>> variant_type;
//
//	variant_type vt = "fer";
//	variant_type vt2 = {"fer"};
//	variant_type vt3 = {"fer", "fer2"};
//
//	//std::vector<std::string> v = {"fer", "fer2"};
//
//
//	boost::spirit::utree u = "fer";
//	//boost::spirit::utree u2 = {"fer", "fer2"};
//
//
//	typedef other_variant<int, double> ov_type;
//
//	ov_type ov;
//	other_variant<int> ov2;
//	other_variant<> ov3;
//
//	std::cout << typeid(ov.u.e).name() << std::endl;
//	std::cout << typeid(ov::base.u.e).name() << std::endl;
//
//
//
////	union U
////	{
////		int i;
////	};
////
////	std::cout << sizeof(U) << std::endl;
////
////	union U2
////	{
////		int i;
////		float f;
////	};
////
////	std::cout << sizeof(U2) << std::endl;
////
////	union U3
////	{
////		int i;
////		float f;
////		U2 u2;
////	};
////
////	std::cout << sizeof(U3) << std::endl;
////
////
////	union U4
////	{
////		double d;
////		U3 u3;
////	};
////
////	std::cout << sizeof(U4) << std::endl;
////
////	U4 u4;
////
////	u4.u3.u2.i = 654;
////	std::cout << u4.u3.u2.i << std::endl;
////	std::cout << u4.d << std::endl;
//
//
//
//	//------------------------------------------------------------------------
//
//
//
//
//
//	initialize();
//
//	//for ( auto item : testcases )
//	//{
//	//	test(item.first, item.second);
//	//}
//
//
//
//
//
//	auto it = testcases.begin();
//	auto end = testcases.end();
//	for ( ; it != end; ++it )
//	{
//		auto item = *it;
//		test(item.first, item.second);
//	}
//
//
//	std::cout << "ok_results: " << ok_results << std::endl;
//	std::cout << "error_results: " << error_results << std::endl;
//
//
//	//using boost::uri_template::uri_template;
//	////using boost::match;
//	//using boost::uri_template::expand;
//	////uri_template uri_tem("{var}");
//	//
//	//std::string res = expand("{var}", variables);
//
//
//
//	//TEMPLATE = re.compile("{([^\}]+)}")
//	//std::string input( "{var}{hello}{empty}{path}{x}{y}" );
//	//sregex re = as_xpr('{') >> (s1= +(~(set= '}'))) >> '}';
//	//std::string output = regex_replace(input, re, format_fun);
//
//
//
//	return 0;
//}
