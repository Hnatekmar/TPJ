#include "../include/CompilerException.h"
#include <sstream>

CompilerException::CompilerException(const std::string errorMessage, const Token token) : 	m_errorMessage(errorMessage),
												m_token(token)
{
}

std::string CompilerException::what() const
{
	std::stringstream ss;
	ss << '<' << m_token.filePos.line << ':' << m_token.filePos.pos << "> Token: " << m_token << " " << m_errorMessage;
	return ss.str();
}
