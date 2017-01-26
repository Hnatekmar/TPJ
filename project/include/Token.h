#ifndef TOKEN_H
#define TOKEN_H

#include "Type.h"
#include "FilePos.h"
#include <iostream>
/**
 * @brief Označuje typ, který se v tokenu nachází
 */
enum class TokenType
{
	L_PAREN, // (
	R_PAREN, // )
	IDENTIFIER, // [a-zA-Z_\-@!?@#$%*+-/]+
	NUMBER, // [0-9]+
	STRING, // "[^\|\.*]*"
	BOOL,
	FUNCTION,
	LIST,
	END_OF_PROGRAM,
    MACRO_FN,
    VECTOR,
    GRAPHICS_ELEMENT,
    EXPANSION
};

struct Token
{
	TokenType type = TokenType::NUMBER;
	MirageType value = 0.0f;
    FilePos filePos = {};
    bool quote = false;
};

std::ostream& operator<<(std::ostream& stream, const Token& token);

#endif
