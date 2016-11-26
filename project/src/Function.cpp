#include "../include/Function.h"

Function::Function(std::deque<Token>& semanticDeque) :	m_code(),
							m_arguments()
{
	if(semanticDeque.front().type != TokenType::L_PAREN)
	{
		// CHYBA: funkce nemá argumenty
	}
	semanticDeque.pop_front();
	// (* x y z))
	while(semanticDeque.front().type != TokenType::R_PAREN)
	{
		if(semanticDeque.front().type != TokenType::IDENTIFIER)
		{
			// CHYBA: argument nemůže být nic jiného než identifikátor
		}
		m_code.push_back(semanticDeque.front());
		semanticDeque.pop_front();
	}
	semanticDeque.pop_front();

	// Načítání těla funkce
	while(!semanticDeque.empty())
	{
		m_code.push_back(semanticDeque.front());
		semanticDeque.pop_front();
	}
	m_code.pop_back();
}
