#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "Token.h"
#include <assert.h>
#include <cctype>

class Lexer
{
	std::istream& m_input;
	int m_char;
	bool m_stopped;

	/**
	 * Načte další znak do m_char pokud není lexer zastavený
	 */
	void next();

	std::string readNumber();
	std::string readString();
	std::string readIdentifier();
	public:
		Lexer(std::istream& input);

		/**
		 * Vrátí další token získaný ze streamu. Pokud se ve streamu nenachází další znaky, tak vrátí END_OF_PROGRAM token.
		 */
		Token nextToken();
};

#endif
