#ifndef AST_H
#define AST_H

#include <list>
#include <memory>
#include "../include/Token.h"

struct AST
{
	std::list<std::shared_ptr<AST>> children;
	Token value;
	std::shared_ptr<AST> root;
	bool call = false;
	AST(Token token, std::shared_ptr<AST>& parent);
};

#endif
