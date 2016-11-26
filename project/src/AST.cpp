#include "../include/AST.h"
#include <iostream>

AST::AST(Token token, std::shared_ptr<AST>& parent) :
					children(),
					value(token),
					root(parent)
{
}
