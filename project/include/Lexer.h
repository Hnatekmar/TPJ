#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "Token.h"
#include <exception>
#include <assert.h>
#include <cctype>

class Lexer
{
	enum class State
	{
		q_s,
		q_a,
		q_b,
		q_c,
		q_d,
		q_e,
		q_f,
		q_final
	};
	std::istream& m_input;
	char m_char;
	bool m_eof;

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
