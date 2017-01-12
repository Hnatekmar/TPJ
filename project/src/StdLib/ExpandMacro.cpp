#include "../../include/StdLib/ExpandMacro.h"
#include "../../include/CompilerException.h"

Token ExpandMacro::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    if(args.size() != 2)
    {
        throw InterpreterException("Makro expanze bere pouze 1 argument a to výraz makra", args.at(0)->evaluate(context));
    }
    std::shared_ptr<AST>& evaluated = args.at(1);
    if(!evaluated->call)
    {
        throw InterpreterException("Musí být volání", evaluated->evaluate(context));
    }
    Token identifier = evaluated->value;
    identifier = evaluateIdentifier(identifier, context);
    if(identifier.type != TokenType::MACRO_FN)
    {
        throw InterpreterException("Musí být makro", identifier);
    }
    auto newAst = boost::get<std::shared_ptr<IMacro>>(identifier.value)->expand(evaluated->children, context);
    return quote(newAst);
}
