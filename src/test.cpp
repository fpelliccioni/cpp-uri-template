// g++ -I"D:\Program Files\Boost\boost_1_49_0" -std=c++11 test.cpp

// http://tools.ietf.org/html/rfc6570
// http://code.google.com/p/uri-templates/source/browse/trunk/testdata.json



#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include <boost/xpressive/xpressive.hpp>

//#include "uri_template.hpp"

using namespace boost::xpressive;

#ifndef _MSC_VER
//using strmap = std::unordered_map<std::string, std::string>;
using strmap = std::map<std::string, std::string>;
#else
typedef std::map<std::string, std::string> strmap;
#endif

strmap variables;
strmap testcases;

sregex re = as_xpr('{') >> (s1= +(~(set= '}'))) >> '}';

//const char* operators = "+./;?|!@";
const char operators[] = "+./;?|!@";

int ok_results = 0;
int error_results = 0;

void initialize()
{
#ifndef _MSC_VER

	variables = {
		{"var"   , "value"}
		, {"hello" , "Hello World!"}
		, {"empty" , ""}
		, {"path"  , "/foo/bar"}
		, {"x"     , "1024"}
		, {"y"     , "768"}
	};
	//, {"list"  , [ "val1", "val2", "val3" ]}
	//, {"keys"  , {"key1": "val1", "key2": "val2"}}


	testcases = {
		{"{var}", "value"}
		, {"{hello}", "Hello%20World%21"}
		, {"{path}/here", "%2Ffoo%2Fbar/here"}
		, {"{x,y}", "1024,768"}
		, {"{var=default}", "value"}
		, {"{undef=default}", "default"}
		//, {"{list}", "val1,val2,val3"}
		//, {"{list*}", "val1,val2,val3"}
		//, {"{list+}", "list.val1,list.val2,list.val3"}
		//, {"{keys}", "key1,val1,key2,val2"}
		//, {"{keys*}", "key1,val1,key2,val2"}
		//, {"{keys+}", "keys.key1,val1,keys.key2,val2"}
		, {"{+var}", "value"}
		, {"{+hello}", "Hello%20World!"}
		, {"{+path}/here", "/foo/bar/here"}
		, {"{+path,x}/here", "/foo/bar,1024/here"}
		, {"{+path}{x}/here", "/foo/bar1024/here"}
		, {"{+empty}/here", "/here"}
		, {"{+undef}/here", "/here"}
		//, {"{+list}", "val1,val2,val3"}
		//, {"{+list*}", "val1,val2,val3"}
		//, {"{+list+}", "list.val1,list.val2,list.val3"}
		//, {"{+keys}", "key1,val1,key2,val2"}
		//, {"{+keys*}", "key1,val1,key2,val2"}
		//, {"{+keys+}", "keys.key1,val1,keys.key2,val2"}
		, {"{;x,y}", ";x=1024;y=768"}
		, {"{;x,y,empty}", ";x=1024;y=768;empty"}
		, {"{;x,y,undef}", ";x=1024;y=768"}
		//, {"{;list}", ";val1,val2,val3"}
		//, {"{;list*}", ";val1;val2;val3"}
		//, {"{;list+}", ";list=val1;list=val2;list=val3"}
		//, {"{;keys}", ";key1,val1,key2,val2"}
		//, {"{;keys*}", ";key1=val1;key2=val2"}
		//, {"{;keys+}", ";keys.key1=val1;keys.key2=val2"}
		, {"{?x,y}", "?x=1024&y=768"}
		, {"{?x,y,empty}", "?x=1024&y=768&empty"}
		, {"{?x,y,undef}", "?x=1024&y=768"}
		//, {"{?list}", "?list=val1,val2,val3"}
		//, {"{?list*}", "?val1&val2&val3"}
		//, {"{?list+}", "?list=val1&list=val2&list=val3"}
		//, {"{?keys}", "?keys=key1,val1,key2,val2"}
		//, {"{?keys*}", "?key1=val1&key2=val2"}
		//, {"{?keys+}", "?keys.key1=val1&keys.key2=val2"}
		, {"{/var}", "/value"}
		, {"{/var,empty}", "/value/"}
		, {"{/var,undef}", "/value"}
		//, {"{/list}", "/val1,val2,val3"}
		//, {"{/list*}", "/val1/val2/val3"}
		//, {"{/list*,x}", "/val1/val2/val3/1024"}
		//, {"{/list+}", "/list.val1/list.val2/list.val3"}
		//, {"{/keys}", "/key1,val1,key2,val2"}
		//, {"{/keys*}", "/key1/val1/key2/val2"}
		//, {"{/keys+}", "/keys.key1/val1/keys.key2/val2"}
		, {"X{.var}", "X.value"}
		, {"X{.empty}", "X"}
		, {"X{.undef}", "X"}
		//, {"X{.list}", "X.val1,val2,val3"}
		//, {"X{.list*}", "X.val1.val2.val3"}
		//, {"X{.list*,x}", "X.val1.val2.val3.1024"}
		//, {"X{.list+}", "X.list.val1.list.val2.list.val3"}
		//, {"X{.keys}", "X.key1,val1,key2,val2"}
		//, {"X{.keys*}", "X.key1.val1.key2.val2"}
		//, {"X{.keys+}", "X.keys.key1.val1.keys.key2.val2"}
	};


#else
	variables["var"] = "value";
	variables["hello"] = "Hello World!";
	variables["empty"] = "";
	variables["path"] = "/foo/bar";
	variables["x"] = "1024";
	variables["y"] = "768";
	//, {"list"  , [ "val1", "val2", "val3" ]}
	//, {"keys"  , {"key1": "val1", "key2": "val2"}}


	testcases["{var}"] = "value";
	testcases["{hello}"] = "Hello%20World%21";
	testcases["{path}/here"] = "%2Ffoo%2Fbar/here";
	testcases["{x,y}"] = "1024,768";
	testcases["{var=default}"] = "value";
	testcases["{undef=default}"] = "default";
	//testcases["{list}"] = "val1,val2,val3";
	//testcases["{list*}"] = "val1,val2,val3";
	//testcases["{list+}"] = "list.val1,list.val2,list.val3";
	//testcases["{keys}"] = "key1,val1,key2,val2";
	//testcases["{keys*}"] = "key1,val1,key2,val2";
	//testcases["{keys+}"] = "keys.key1,val1,keys.key2,val2";
	testcases["{+var}"] = "value";
	testcases["{+hello}"] = "Hello%20World!";
	testcases["{+path}/here"] = "/foo/bar/here";
	testcases["{+path,x}/here"] = "/foo/bar,1024/here";
	testcases["{+path}{x}/here"] = "/foo/bar1024/here";
	testcases["{+empty}/here"] = "/here";
	testcases["{+undef}/here"] = "/here";
	//testcases["{+list}"] = "val1,val2,val3";
	//testcases["{+list*}"] = "val1,val2,val3";
	//testcases["{+list+}"] = "list.val1,list.val2,list.val3";
	//testcases["{+keys}"] = "key1,val1,key2,val2";
	//testcases["{+keys*}"] = "key1,val1,key2,val2";
	//testcases["{+keys+}"] = "keys.key1,val1,keys.key2,val2";
	testcases["{;x,y}"] = ";x=1024;y=768";
	testcases["{;x,y,empty}"] = ";x=1024;y=768;empty";
	testcases["{;x,y,undef}"] = ";x=1024;y=768";
	//testcases["{;list}"] = ";val1,val2,val3";
	//testcases["{;list*}"] = ";val1;val2;val3";
	//testcases["{;list+}"] = ";list=val1;list=val2;list=val3";
	//testcases["{;keys}"] = ";key1,val1,key2,val2";
	//testcases["{;keys*}"] = ";key1=val1;key2=val2";
	//testcases["{;keys+}"] = ";keys.key1=val1;keys.key2=val2";
	testcases["{?x,y}"] = "?x=1024&y=768";
	testcases["{?x,y,empty}"] = "?x=1024&y=768&empty";
	testcases["{?x,y,undef}"] = "?x=1024&y=768";
	//testcases["{?list}"] = "?list=val1,val2,val3";
	//testcases["{?list*}"] = "?val1&val2&val3";
	//testcases["{?list+}"] = "?list=val1&list=val2&list=val3";
	//testcases["{?keys}"] = "?keys=key1,val1,key2,val2";
	//testcases["{?keys*}"] = "?key1=val1&key2=val2";
	//testcases["{?keys+}"] = "?keys.key1=val1&keys.key2=val2";
	testcases["{/var}"] = "/value";
	testcases["{/var,empty}"] = "/value/";
	testcases["{/var,undef}"] = "/value";
	//testcases["{/list}"] = "/val1,val2,val3";
	//testcases["{/list*}"] = "/val1/val2/val3";
	//testcases["{/list*,x}"] = "/val1/val2/val3/1024";
	//testcases["{/list+}"] = "/list.val1/list.val2/list.val3";
	//testcases["{/keys}"] = "/key1,val1,key2,val2";
	//testcases["{/keys*}"] = "/key1/val1/key2/val2";
	//testcases["{/keys+}"] = "/keys.key1/val1/keys.key2/val2";
	testcases["X{.var}"] = "X.value";
	testcases["X{.empty}"] = "X";
	testcases["X{.undef}"] = "X";
	//testcases["X{.list}"] = "X.val1,val2,val3";
	//testcases["X{.list*}"] = "X.val1.val2.val3";
	//testcases["X{.list*,x}"] = "X.val1.val2.val3.1024";
	//testcases["X{.list+}"] = "X.list.val1.list.val2.list.val3";
	//testcases["X{.keys}"] = "X.key1,val1,key2,val2";
	//testcases["X{.keys*}"] = "X.key1.val1.key2.val2";
	//testcases["X{.keys+}"] = "X.keys.key1.val1.keys.key2.val2";

#endif
}



template <typename T, size_t Size>
const T* find( const T (&array)[Size],  T const& value )
{
	//return &(array[0]);
	return std::find( std::begin(array), std::end(array), value );
}

template <typename T, size_t Size>
const T* array_end( const T (&array)[Size] )
{
	return &(array[Size]);
}


//template<class InputIterator, class T>
//InputIterator find ( InputIterator first, InputIterator last, const T& value )
//{
//	for ( ;first!=last; first++) if ( *first==value ) break;
//	return first;
//}



std::string const& format_fun(smatch const& what)
{
	//TODO: Procesar caracteres especiales en variables.second
		//Ejemplo ["{hello}", "Hello%20World%21"],


	auto text = what[1].str();


	char op;

	auto chr = text[0];

	auto xxx = find(operators, chr);
	if (xxx != std::end(operators))
	{
		op = chr;
	}






	//OPERATOR = "+./;?|!@"

	return variables[ text ];
}


void test( std::string const& uritemplate, std::string const& expected )
{
	std::string output = regex_replace(uritemplate, re, format_fun);

	if (output != expected)
	{
		std::cout << "ERROR \t\t template: " << uritemplate << "\t\texpected: " << expected << "\t\tresult: " << output << std::endl;
		error_results++;
	}
	else
	{
		std::cout << "OK \t\t template: " << uritemplate << "\t\texpected: " << expected << "\t\tresult: " << output << std::endl;
		ok_results++;
	}
}


int main( /* int argc, char* argv[] */ )
{
	initialize();

	//for ( auto item : testcases )
	//{
	//	test(item.first, item.second);
	//}





	auto it = testcases.begin();
	auto end = testcases.end();
	for ( ; it != end; ++it )
	{
		auto item = *it;
		test(item.first, item.second);
	}


	std::cout << "ok_results: " << ok_results << std::endl;
	std::cout << "error_results: " << error_results << std::endl;
		

	//using boost::uri_template::uri_template;
	////using boost::match;
	//using boost::uri_template::expand;
	////uri_template uri_tem("{var}");
	//
	//std::string res = expand("{var}", variables);



	//TEMPLATE = re.compile("{([^\}]+)}")
	//std::string input( "{var}{hello}{empty}{path}{x}{y}" );
	//sregex re = as_xpr('{') >> (s1= +(~(set= '}'))) >> '}';
	//std::string output = regex_replace(input, re, format_fun);



	return 0;
}
