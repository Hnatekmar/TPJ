#include "../include/CompilerException.h"
#include <sstream>
#include <algorithm>

InterpreterException::InterpreterException(const std::string errorMessage, const Token token) : 	m_errorMessage(errorMessage),
												m_token(token)
{
}

std::string InterpreterException::what() const
{
	std::stringstream ss;
    ss << std::endl;
    ss << '<' << m_token.filePos.line << ':' << m_token.filePos.pos << "> Hodnota: " << m_token << " " << m_errorMessage;
	return ss.str();
}
