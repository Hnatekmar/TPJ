#include "../include/AST.h"
#include <iostream>
#include "../include/CompilerException.h"

AST::AST(Token token, std::shared_ptr<AST>& parent, bool isCall):
					call(isCall),
					root(parent),
					value(token),
					children()
{
}

MirageType AST::evaluate(Context& context)
{
	if(call)
	{
		return value.value;
	}
	else
	{
		return value.value;
	}
}
