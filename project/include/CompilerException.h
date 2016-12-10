#ifndef COMPILER_EXCEPTION_H
#define COMPILER_EXCEPTION_H

#include <exception>
#include <string>
#include "Token.h"

/**
 * @brief Vyj
 */
class InterpreterException
{
	const std::string m_errorMessage;
	const Token m_token;
	public:
		InterpreterException(const std::string errorMessage, const Token token);
		std::string what() const;
};

#endif
