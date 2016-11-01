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

Token Lexer::nextToken()
{
	State state = State::q_s;
	Token token;
	while(state != State::q_final)
	{
		if(m_eof)
		{
			if(state != State::q_s)
			{
				std::cerr << "EOF v průběhu lexikální analýzi";
			}
		}
		
		next();
		if(state == State::q_s)
		{
			if(m_char == '\n' || m_char == '\t' || m_char == ' ')
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
				token.value = m_char;
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
		std::cerr << "Neočekávaný znak " << m_char;
		std::exit(9001);
		//throw std::runtime_error("Neočekávaný znak " + m_char);
	}
	return token;
}

std::string Lexer::readNumber()
{
	std::string number;
	while(isdigit(m_char))
	{
		number += m_char;
		next();
	}
	return number;
}

std::string Lexer::readString()
{
	std::string string;
	assert(m_char == '"'); // String musí začínat na "
	next();
	bool escape = false;
	while(m_char != '"' || escape)
	{
		string += m_char;
		next();
		// TODO: ERROR reporting
	}
	assert(m_char == '"'); // String musí končit na "
	return string;
}

std::string Lexer::readIdentifier()
{
	std::string identifier;
	return identifier;
}
