#include "../include/Lexer.h"

Lexer::Lexer(std::istream& input):	m_input(input),
					m_char(' '),
					m_eof(false),
					m_filePos()
{
}

void Lexer::next()
{
	m_input >> std::noskipws >> m_char;
	m_filePos.accept(m_char);
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
	std::string value;
	while(state != State::q_final)
	{
		next();
		if(m_eof)
		{
			if(state != State::q_s && state != State::q_af && state != State::q_bf 
				 && state != State::q_cf && state != State::q_final && state != State::q_f)
			{
				std::cerr << "EOF v průběhu lexikální analýzy";
				std::exit(9001);
			}
			else
			{
				token.type = TokenType::END_OF_PROGRAM;
				value = "END_OF_PROGRAM";
				token.value = value;
				return token;
			}
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
				value += m_char;
				token.type = TokenType::NUMBER;
				state = State::q_bf;
				continue;
			}

			if((isalpha(m_char) || isprint(m_char)) && m_char != ';' && m_char != ')' && m_char != '(' && !isspace(m_char) && m_char != '"')
			{
				value += m_char;
				token.type = TokenType::IDENTIFIER;
				state = State::q_af;
				continue;
			}

			if(m_char == ')')
			{
				value = m_char;
				token.type = TokenType::R_PAREN;
				token.value = value;
				break;
			}

			if(m_char == '(')
			{
				value = m_char;
			token.type = TokenType::L_PAREN;
				token.value = value;
				break;
			}

			if(m_char == '"')
			{
				state = State::q_d;
				token.type = TokenType::STRING;
				token.value = value;
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
				value += m_char;
				continue;
			}
			else if(m_char == '.')
			{
				value += m_char;
				state = State::q_c;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				token.value = std::stof(value);
				break; // Q_BF je finální stav automatu, takže můžeme zastavit zde
			}
		}

		if(state == State::q_c)
		{
			if(isdigit(m_char))
			{
				value += m_char;
				state = State::q_cf;
				continue;
			}
		}

		if(state == State::q_cf)
		{
			if(isdigit(m_char))
			{
				value += m_char;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				token.value = std::stof(value);
				break; // Q_CF je finální stav automatu, takže můžeme zastavit zde
			}
		}

		if(state == State::q_af)
		{
			if((isalpha(m_char) || isdigit(m_char) || isprint(m_char)) && m_char != ';' && m_char != ')' && m_char != '(' && !isspace(m_char) && m_char != '"')
			{
				value += m_char;
				continue;
			}
			else
			{
				m_input.putback(m_char);
				token.value = value;
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
				token.value = value;
				break;
			}
			else if(m_char == '\\')
			{
				state = State::q_e;
				continue;
			}
			else
			{
				value += m_char;
				continue;
			}
		}

		if(state == State::q_e)
		{
			value += m_char;
			state = State::q_d;
			continue;
		}

		std::cerr << '<' << m_filePos.line << ":" << m_filePos.pos << "> Neočekávaný znak " << m_char << std::endl;
		std::exit(9001);
		//throw std::runtime_error("Neočekávaný znak " + m_char);
	}
	token.filePos = m_filePos;
	if(token.type == TokenType::IDENTIFIER)
	{
		std::string value = boost::get<std::string>(token.value);
		if(value == "PRAVDA")
		{
			token.value = true;
			token.type = TokenType::BOOL;
		}
		if(value == "NEPRAVDA")
		{
			token.value = false;
			token.type = TokenType::BOOL;
		}
	}
	return token;
}
