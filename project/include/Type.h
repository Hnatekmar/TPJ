#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include "../include/Vector.h"

struct AST;
struct Token;
class IFunction;
class IMacro;

typedef boost::make_recursive_variant<std::function<Token(std::vector<std::shared_ptr<AST>>&, 
        std::map<std::string, Token>&)>,
		float,
		std::string,
		std::list<Token>,
		Vector,
        std::shared_ptr<IFunction>,
        std::shared_ptr<IMacro>,
		bool>::type MirageType;

typedef std::map<std::string, Token> Context;
enum class MirageKind
{
	function = 0,
	number = 1,
	string = 2,
    list = 3,
    vector = 4,
    functionClass = 5,
    macro_fn = 6,
    boolean = 7
};

/**
 * @brief Vrátí druh typu na základě metody whitch
 */
MirageKind getKind(const MirageType& type);

#endif
