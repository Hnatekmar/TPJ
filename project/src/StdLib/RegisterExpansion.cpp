#include "../../include/StdLib/RegisterExpansion.h"
#include "../../include/CompilerException.h"

RegisterExpansion::RegisterExpansion()
{
    m_args = {
        "nazev",
        "hodnota"
    };
}

std::shared_ptr<AST> RegisterExpansion::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    auto identifier = copy.at("nazev");
    if(identifier.type != TokenType::IDENTIFIER)
    {
        throw InterpreterException("Název musí být typu identifikátor", identifier);
    }
    auto value = unquote(copy.at("hodnota"))->evaluate(context);
    if(value.type != TokenType::FUNCTION && value.type != TokenType::MACRO_FN)
    {
        throw InterpreterException("Hodnota musí být funkce nebo makro", value);
    }
    context["#" + boost::get<std::string>(identifier.value)] = value;
    return unquote(copy.at("hodnota"));
}
