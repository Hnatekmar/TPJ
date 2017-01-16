#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include "List.h"
#include <map>
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
        List<Token>,
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
    function = 3,
    macro_fn = 4,
    boolean = 5,
    GraphicsObject = 6
};

/**
 * @brief Vrátí druh typu na základě metody which
 */
MirageKind getKind(const MirageType& type);

#endif
