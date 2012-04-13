#include <string>

#include "uri_template.hpp"


int main( /* int argc, char* argv[] */ )
{
	using boost::uri_template::uri_template;
	//using boost::match;

	std::string uri = "/order/1";
	uri_template uri_tem("/order/{orderid}");

	bool res = match(uri_tem, uri);

	return 0;
}
