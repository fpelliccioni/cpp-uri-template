#ifndef uri_template_HPP__
#define uri_template_HPP__

#include <string>
#include <vector>

#include "detail/uri_template_expression.hpp"

namespace boost {
namespace uri_template {
	

struct uri_template
{
	explicit uri_template( std::string const& text )
		: text_(text)
	{}

	std::string text_;
	std::vector<detail::uri_template_expression> expression_;
};

bool match( uri_template const& uri_tmplt, std::string const& uri )
{
	return false;
}


} // namespace uri_template
} // namespace boost


#endif // uri_template_HPP__