#include "../include/Parser.h"
#include <cassert>
#include <stack>

Parser::Parser(Lexer& lexer) :	m_lexer(lexer),
				m_constants()
{
}

void Parser::sCall(std::deque<Token>& semanticDeque)
{
	/**
	* SCall(semanticDeque) -> { // Sémantická akce volání
	*	assert(semanticDeque.peek() == '(');
	*	semanticDeque.pop();
	*	identifier = semanticDeque.peek();
	*	if(id == '(') // Pokud je id volání
	*	{
	*		SCall(semanticDeque);
	*	}
	*	else
	*	{
	*		m_functions.at(id)(semanticDeque); // Volání
	*	}
	* }
	*/
	Token currToken = semanticDeque.front();
	assert(currToken.type == TokenType::L_PAREN);
	semanticDeque.pop_front();
	currToken = semanticDeque.front();
	if(currToken.type == TokenType::L_PAREN)
	{
		sCall(semanticDeque);
	}
	else if(currToken.type == TokenType::IDENTIFIER)
	{
		auto functionIdentifier = boost::get<std::string>(currToken.value);
		semanticDeque.pop_front();
		if(m_functions.find(functionIdentifier) != m_functions.end())
		{
			m_functions.at(functionIdentifier)(semanticDeque);
		}
		else
		{
			throw CompilerException("Neznámá funkce " + functionIdentifier, currToken);
		}
	}
	else
	{
		throw CompilerException("Token není identifikátor nebo volání", currToken);
	}
}

void Parser::parse()
{
	std::stack<Rule> stack;
	stack.push(Rule::Start);
	Token token = m_lexer.nextToken();
	auto rule = stack.top();
	std::deque<Token> semanticDeque;
	while(!stack.empty())
	{
		rule = stack.top();
		stack.pop();
		if(rule == Rule::SCall)
		{
			sCall(semanticDeque);
			if(!semanticDeque.empty())
			{
				semanticDeque.pop_front();
			}
		}
		else if(isTerminal(rule) || rule == Rule::epsilon)
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				semanticDeque.push_back(token);
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
				semanticDeque.push_back(token);
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::epsilon)
			{
				semanticDeque.push_back(token);
				token = m_lexer.nextToken();
				stack.pop();
			}
			else if(rule == Rule::END_OF_PROGRAM && token.type == TokenType::END_OF_PROGRAM)
			{
				assert(stack.empty());
				assert(semanticDeque.empty());
				break;
			}
			else if(rule == Rule::atom && isAtom(token))
			{
				semanticDeque.push_back(token);
				token = m_lexer.nextToken();
			}
			else
			{
				throw CompilerException("Neočekavany token", token);
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
			throw CompilerException("Přepisovací pravidlo nenalezeno", token);
		}
	}
	if(!m_lexer.eof())
	{
		throw CompilerException("Neočekávaný konec parsování", token);
	}
}
