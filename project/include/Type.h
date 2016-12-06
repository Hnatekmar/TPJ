#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>
#include <map>
#include <functional>
#include <vector>
#include <iostream>
#include <memory>

struct AST;
struct Token;

typedef boost::make_recursive_variant<std::function<Token(std::vector<std::shared_ptr<AST>>, 
		std::map<std::string, Token>&)>,
		float,
		std::string,
		bool>::type MirageType;

typedef std::map<std::string, Token> Context;

enum class MirageKind
{
	function = 0,
	number = 1,
	string = 2,
	boolean = 3
};
/**
 * @brief Vrátí druh typu na základě metody whitch
 */
MirageKind getKind(const MirageType& type);

#endif
