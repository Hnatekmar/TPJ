#ifndef TOKEN_H
#define TOKEN_H

#include "Type.h"

enum class TokenType
{
	L_PAREN, // (
	R_PAREN, // )
	IDENTIFIER, // [a-zA-Z_\-@!?@#$%*+-/]+
	NUMBER, // [0-9]+
	STRING, // "[^\|\.*]*"
	BOOL,
	END_OF_PROGRAM
};

struct Token
{
	TokenType type = TokenType::NUMBER;
	MirageType value = 0.0f;
};

#endif /* end of include guard: TOKEN_H */
