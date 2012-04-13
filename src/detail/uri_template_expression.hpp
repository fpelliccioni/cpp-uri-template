#ifndef uri_template_expression_HPP__
#define uri_template_expression_HPP__


#include <string>

namespace boost {
namespace uri_template {
namespace detail {


struct uri_template_expression
{

	uri_template_expression ( int position, std::string const& expression, bool is_query )
		: position_(position), expression_(expression), is_query_(is_query)
	{
		//operator := '%U'

	}
		  

	int position_;
	std::string expression_;
	bool is_query_;
	//operator := '%U'

};


} // namespace detail
} // namespace uri_template
} // namespace boost


#endif // uri_template_expression_HPP__