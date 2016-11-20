#ifndef COMPILER_EXCEPTION_H
#define COMPILER_EXCEPTION_H

#include <exception>
#include <string>

class CompilerException
{
	const std::string m_errorMessage;
	public:
		CompilerException(const std::string errorMessage);
		std::string what() const;
};

#endif
