#include "../include/AST.h"
#include <iostream>
#include "../include/CompilerException.h"
#include "../include/IFunction.h"
#include "../include/StdLib/Macro.h"

Token evaluateIdentifier(Token identifier, const Context& context)
{
    while((identifier.type == TokenType::IDENTIFIER || identifier.type == TokenType::EXPANSION) && !identifier.quote)
	{
		std::string value = boost::get<std::string>(identifier.value);
		if(context.find(value) != context.end())
		{
			identifier = context.at(value);
		}
		else
		{
			throw InterpreterException("Token nelze přeložit.", identifier);
		}
	}
	return identifier;
}

AST::AST(Token token, std::shared_ptr<AST>& parent, bool isCall):
					call(isCall),
					root(parent),
					value(token),
					children()
{
}

Token AST::evaluate(Context& context)
{
    if(call)
    {
        if(children.size() == 0)
        {
            throw InterpreterException("Snažíte se evaluovat prázdný list ()", {});
        }
		Token identifier = children.front()->evaluate(context);
        if(identifier.type == TokenType::IDENTIFIER || identifier.type == TokenType::EXPANSION)
		{
			identifier = evaluateIdentifier(identifier, context);
		}
        if(identifier.type != TokenType::FUNCTION && identifier.type != TokenType::MACRO_FN)
		{
            throw InterpreterException("Volaná hodnota není funkce nebo makro", identifier);
		}
		auto fnType = getKind(identifier.value);
        if(fnType == MirageKind::function)
        {
            return boost::get<std::shared_ptr<IFunction>>(identifier.value)->execute(children, context);
        }
        else if(fnType == MirageKind::macro_fn)
        {
            auto newAst = boost::get<std::shared_ptr<IMacro>>(identifier.value)->expand(children, context);
            return newAst->evaluate(context);
        }
	}
	else
	{
        if(value.type == TokenType::IDENTIFIER && !value.quote)
		{
			return evaluateIdentifier(value, context);
		}
		else
		{
			return value;
		}
    }
    return Token{};
}
