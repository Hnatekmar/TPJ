#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>
#include <map>
#include <memory>
#include <functional>

struct Token;
struct AST;

typedef boost::make_recursive_variant<std::function<Token(
		std::map<std::string, Token>&,
		std::list<std::shared_ptr<AST>>&)>,
		float,
		std::list<Token>,
		std::string,
		bool>::type MirageType;

#endif
