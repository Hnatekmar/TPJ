#ifndef FUNCTION_H
#define FUNCTION_H

#include <deque>
#include <list>
#include "Token.h"

class Function
{
	std::deque<Token> m_code;
	std::list<Token> m_arguments;
	public:
		Function(std::deque<Token>& semanticDeque);
};

#endif
