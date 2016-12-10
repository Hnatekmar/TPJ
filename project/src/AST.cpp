#include "../include/AST.h"
#include <iostream>
#include "../include/CompilerException.h"
#include "../include/IFunction.h"

inline Token evaluateIdentifier(Token identifier, const Context& context)
{
	while(identifier.type == TokenType::IDENTIFIER)
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
	if(call && !quote)
	{
		Token identifier = children.front()->evaluate(context);
		if(identifier.type == TokenType::IDENTIFIER)
		{
			identifier = evaluateIdentifier(identifier, context);
		}
		if(identifier.type != TokenType::FUNCTION)
		{
			throw InterpreterException("Volaná hodnota není funkce", identifier);
		}
		auto fnType = getKind(identifier.value);
        if(fnType == MirageKind::function)
        {
            auto function = (boost::get<std::function<Token(std::vector<std::shared_ptr<AST>>&, Context&)>>)(identifier.value);
            return function(children, context);
        }
        else
        {
            return boost::get<std::shared_ptr<IFunction>>(identifier.value)->execute(children, context);
        }
	}
	else
	{
		if(value.type == TokenType::IDENTIFIER && !quote)
		{
			return evaluateIdentifier(value, context);
		}
		else
		{
			return value;
		}
	}
}
