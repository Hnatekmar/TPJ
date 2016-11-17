#include "../include/Parser.h"
#include <stack>

Parser::Parser(Lexer& lexer) : m_lexer(lexer)
{
}

void Parser::parse()
{
	std::stack<Rule> stack;
	stack.push(Rule::Start);
	auto token = m_lexer.nextToken();
	bool call = false;
	while(!stack.empty())
	{
		auto rule = stack.top();
		stack.pop();
		if(isTerminal(rule) || rule == Rule::epsilon)
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				std::cout << "Sémantická akce VOLÁNÍ:" << std::endl;
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::epsilon)
			{
				stack.pop();
				token = m_lexer.nextToken();
			}
			else if(isAtom(token))
			{
				token = m_lexer.nextToken();
			}
			else
			{
				throw CompilerException("Neočekávaný token");
			}
		}
		else if(hasRule(rule, token.type))
		{
			for(auto it = m_parsingTable[rule][token.type].rbegin(); it != m_parsingTable[rule][token.type].rend(); it++)
			{
				stack.push(*it);
			}
		}
		else
		{
			throw CompilerException("Přepisovací pravidlo nenalezeno");
		}
	}
	if(!m_lexer.eof())
	{
		throw CompilerException("Chyba v kompilátoru neočekávaný konec parsování");
	}
}
