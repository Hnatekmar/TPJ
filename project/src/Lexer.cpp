#include "../include/Lexer.h"

Lexer::Lexer(std::istream& input):	m_input(input),
					m_char(' '),
					m_eof(false)
{
}

void Lexer::next()
{
	m_input >> std::noskipws >> m_char;
	m_eof = m_input.eof();
}

bool Lexer::eof()
{
	return m_eof;
}

Token Lexer::nextToken()
{
	State state = State::q_s;
	Token token;
	while(state != State::q_final)
	{
		next();
		if(m_eof)
		{
			if(state != State::q_s || state != State::q_af || state != State::q_bf 
				 || state != State::q_cf || state != State::q_final)
			{
				std::cerr << "EOF v průběhu lexikální analýzy";
				std::exit(9001);
			}
			break;
		}
		
		if(state == State::q_s) // Startovní stav
		{
			if(std::isspace(m_char))
			{
				continue;
			}

			if(m_char == ';')
			{
				state = State::q_f;
				continue;
			}

			if(isdigit(m_char))
			{
				token.value += m_char;
				token.type = TokenType::NUMBER;
				state = State::q_bf;
				continue;
			}

			if((isalpha(m_char) || isprint(m_char)) && m_char != ';' && m_char != ')' && m_char != '(' && !isspace(m_char))
			{
				token.value += m_char;
				token.type = TokenType::IDENTIFIER;
				state = State::q_af;
				continue;
			}

			if(m_char == ')')
			{
				token.value = m_char;
				token.type = TokenType::R_PAREN;
				break;
			}

			if(m_char == '(')
			{
				token.value = m_char;
				token.type = TokenType::L_PAREN;
				break;
			}

			if(m_char == '"')
			{
				state = State::q_d;
				token.type = TokenType::STRING;
				continue;
			}
		}

		/**
		 * Načítá čísla
		 */
		if(state == State::q_bf)
		{
			if(isdigit(m_char))
			{
				token.value += m_char;
				continue;
			}
			else if(m_char == '.')
			{
				token.value += m_char;
				state = State::q_c;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				break; // Q_BF je finální stav automatu, takže můžeme zastavit zde
			}
		}

		if(state == State::q_c)
		{
			if(isdigit(m_char))
			{
				token.value += m_char;
				state = State::q_cf;
				continue;
			}
		}

		if(state == State::q_cf)
		{
			if(isdigit(m_char))
			{
				token.value += m_char;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				break; // Q_CF je finální stav automatu, takže můžeme zastavit zde
			}
		}

		if(state == State::q_af)
		{
			if((isalpha(m_char) || isdigit(m_char) || isprint(m_char)) && m_char != ';' && m_char != ')' && m_char != '(' && !isspace(m_char))
			{
				token.value += m_char;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				break;
			}
		}

		if(state == State::q_f)
		{
			if(m_char == '\n')
			{
				state = State::q_s;
			}
			continue;
		}

		if(state == State::q_d)
		{
			if(m_char == '"')
			{
				break;
			}
			else if(m_char == '\\')
			{
				state = State::q_e;
				continue;
			}
			else
			{
				token.value += m_char;
				continue;
			}
		}

		if(state == State::q_e)
		{
			token.value += m_char;
			state = State::q_d;
			continue;
		}

		std::cerr << "Neočekávaný znak " << m_char << std::endl;
		std::exit(9001);
		//throw std::runtime_error("Neočekávaný znak " + m_char);
	}
	return token;
}
