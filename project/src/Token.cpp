#include "../include/Token.h"

std::ostream& operator<<(std::ostream& stream, const Token& token)
{
	if(token.type == TokenType::L_PAREN)
	{
		stream << '(';
	}
	if(token.type == TokenType::R_PAREN)
	{
		stream << ')';
	}
	if(token.type == TokenType::IDENTIFIER)
	{
		stream << boost::get<std::string>(token.value);
	}
	if(token.type == TokenType::NUMBER)
	{
		stream << boost::get<float>(token.value);
	}
	if(token.type == TokenType::STRING)
	{
		stream << boost::get<std::string>(token.value);
	}
	if(token.type == TokenType::BOOL)
	{
		stream << boost::get<bool>(token.value);
	}
	if(token.type == TokenType::END_OF_PROGRAM)
	{
		stream << "EOF";
	}
	return stream;
}
