#include "../include/Lexer.h"

Lexer::Lexer(std::istream& input):	m_input(input),
					m_char(' '),
					m_stopped(true)
{
}

void Lexer::next()
{
	if(!m_stopped)
	{
		m_char = m_input.get();
	}
}

Token Lexer::nextToken()
{
	next();
	if(m_char == EOF)
	{
		return {TokenType::END_OF_PROGRAM, ""};
	}
	if(m_char == '(')
	{
		return {TokenType::L_PAREN, "("};
	}
	if(m_char == ')')
	{
		return {TokenType::R_PAREN, "("};
	}
	if(isdigit(m_char))
	{
		return {TokenType::NUMBER, readNumber()};
	}
	if(m_char == '"')
	{
		return {TokenType::STRING, readString()};
	}
	return {TokenType::INVALID_TOKEN, ""};
}

std::string Lexer::readNumber()
{
	std::string number;
	while(isdigit(m_char))
	{
		number += m_char;
		next();
	}
	return number;
}

std::string Lexer::readString()
{
	std::string string;
	assert(m_char == '"'); // String musí začínat na "
	next();
	bool escape = false;
	while(m_char != '"' || escape)
	{
		string += m_char;
		next();
		// TODO: ERROR reporting
	}
	assert(m_char == '"'); // String musí končit na "
	return string;
}

std::string Lexer::readIdentifier()
{
	std::string identifier;
	return identifier;
}
