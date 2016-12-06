#include "../include/AST.h"
#include <iostream>
#include "../include/CompilerException.h"

Token evaluateIdentifier(Token identifier, const Context& context)
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
			throw CompilerException("Token nelze přeložit.", identifier);
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
		Token identifier = children.front()->evaluate(context);
		if(identifier.type == TokenType::IDENTIFIER)
		{
			identifier = evaluateIdentifier(identifier, context);
		}
		if(identifier.type != TokenType::FUNCTION)
		{
			throw CompilerException("Volaná hodnota není funkce", identifier);
		}
		auto function = (boost::get<std::function<Token(std::vector<std::shared_ptr<AST>>, std::map<std::string, Token>&)>>)(identifier.value);
		return function(children, context);
	}
	else
	{
		if(value.type == TokenType::IDENTIFIER)
		{
			return evaluateIdentifier(value, context);
		}
		else
		{
			return value;
		}
	}
}
