#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include "../include/Vector.h"
#include "../include/GraphicsObject.h"

struct AST;
struct Token;
class IFunction;
class IMacro;

typedef boost::variant<float,
		std::string,
		std::list<Token>,
		Vector,
        std::shared_ptr<IFunction>,
        std::shared_ptr<IMacro>,
        bool,
        std::shared_ptr<GraphicsObject>> MirageType;

typedef std::map<std::string, Token> Context;
enum class MirageKind
{
    number = 0,
    string = 1,
    list = 2,
    vector = 3,
    function = 4,
    macro_fn = 5,
    boolean = 6,
    GraphicsObject = 7
};

/**
 * @brief Vrátí druh typu na základě metody whitch
 */
MirageKind getKind(const MirageType& type);

#endif
