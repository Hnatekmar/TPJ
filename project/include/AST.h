#ifndef AST_H
#define AST_H

#include "Token.h"
#include <iostream>
#include <vector>
#include <map>
#include "Type.h"

enum class ASTType
{
	CALL,
	VALUE,
	ROOT
};

/**
 * Třída reprezentující abstraktní syntaktický strom
 */
struct AST
{
	ASTType type;
	MirageType value;
	std::vector<AST> children;
	bool operator==(const AST& right);
};

#endif
