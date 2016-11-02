#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
	L_PAREN, // (
	R_PAREN, // )
	IDENTIFIER, // [a-zA-Z_\-@!?@#$%*+-/]+
	NUMBER, // [0-9]+
	STRING // "[^\|\.*]*"
};

struct Token
{
	TokenType type;
	std::string value;
};

#endif /* end of include guard: TOKEN_H */
