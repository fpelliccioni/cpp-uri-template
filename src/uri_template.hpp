#ifndef uri_template_HPP__
#define uri_template_HPP__

#include <string>
#include <vector>

#include <unordered_map>

#include "detail/uri_template_expression.hpp"



namespace boost {
namespace uri_template {

//using variable_map_type = std::unordered_map<std::string, std::string>;
//
//
//struct uri_template
//{
//	explicit uri_template( std::string const& text )
//		: text_(text)
//	{}
//
//	std::string text_;
//	std::vector<detail::uri_template_expression> expression_;
//};
//
////bool match( uri_template const& uri_tmplt, std::string const& uri )
////{
////	return false;
////}
//
//
//std::string expand( std::string const& uri_tmplt, variable_map_type const& variables )
//{
//	return "";
//}
//

} // namespace uri_template
} // namespace boost


#endif // uri_template_HPP__