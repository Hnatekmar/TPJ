#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "FilePos.h"
#include <iostream>
#include <exception>
#include <assert.h>
#include <cctype>

class Lexer
{
	enum class State
	{
		q_s, // Startovní stav
		q_c, // Desetiná tečka
		q_d, // Řetězec
		q_e, // Řetězec s escape větev
        q_f, // Komentář
        q_g, // Expanze
        q_gf,
        q_h, // pravda/nepravda
		q_af, // Identifikátor
		q_bf, // Číslo před desetinou čárkou
		q_cf, // Číslo za desetinou čárkou
		q_final // Konečný stav automatu
	};
	std::istream& m_input;

	char m_char;
	bool m_eof;
	FilePos m_filePos;

	/**
	 * Načte další znak do m_char pokud není lexer zastavený
	 */
	void next();

	public:
		Lexer(std::istream& input);

		bool eof();

		/**
		 * Vrátí další token získaný ze streamu. Pokud se ve streamu nenachází další znaky, tak vrátí END_OF_PROGRAM token.
		 */
		Token nextToken();
};

#endif
