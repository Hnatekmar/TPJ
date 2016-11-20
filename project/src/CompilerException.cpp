#include "../include/CompilerException.h"


CompilerException::CompilerException(const std::string errorMessage) : m_errorMessage(errorMessage)
{
}

std::string CompilerException::what() const
{
	return m_errorMessage;
}
