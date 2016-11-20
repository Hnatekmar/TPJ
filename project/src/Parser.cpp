#include "../include/Parser.h"
#include <cassert>

Parser::Parser(Lexer& lexer) : m_lexer(lexer)
{
}

void Parser::sCall(std::queue<Token>& semanticStack)
{
	/**
	* SCall(semanticStack) -> { // Sémantická akce volání
	*	assert(semanticStack.peek() == '(');
	*	semanticStack.pop();
	*	identifier = semanticStack.peek();
	*	if(id == '(') // Pokud je id volání
	*	{
	*		SCall(semanticStack);
	*	}
	*	else
	*	{
	*		m_functions.at(id)(semanticStack); // Volání
	*	}
	* }
	*/
	Token currToken = semanticStack.front();
	assert(currToken.type == TokenType::L_PAREN);
	semanticStack.pop();
	currToken = semanticStack.front();
	if(currToken.type == TokenType::L_PAREN)
	{
		sCall(semanticStack);
	}
	else if(currToken.type == TokenType::IDENTIFIER)
	{
		auto functionIdentifier = boost::get<std::string>(currToken.value);
		semanticStack.pop();
		if(m_functions.find(functionIdentifier) != m_functions.end())
		{
			m_functions.at(functionIdentifier)(semanticStack);
		}
		else
		{
			throw CompilerException("Neznámá funkce " + functionIdentifier);
		}
	}
	else
	{
		throw CompilerException(" není identifikátor nebo volání");
	}
}

void Parser::parse()
{
	std::stack<Rule> stack;
	stack.push(Rule::Start);
	Token token = m_lexer.nextToken();
	auto rule = stack.top();
	std::queue<Token> semanticStack;
	while(!stack.empty())
	{
		rule = stack.top();
		stack.pop();
		if(rule == Rule::SCall)
		{
			sCall(semanticStack);
			if(!semanticStack.empty())
			{
				std::cout << "Hodnota výrazu: " << semanticStack.front().value << std::endl;
				semanticStack.pop();
			}
		}
		else if(isTerminal(rule) || rule == Rule::epsilon)
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				semanticStack.push(token);
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
				semanticStack.push(token);
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::epsilon)
			{
				semanticStack.push(token);
				token = m_lexer.nextToken();
				stack.pop();
			}
			else if(rule == Rule::END_OF_PROGRAM && token.type == TokenType::END_OF_PROGRAM)
			{
				assert(stack.empty());
				assert(semanticStack.empty());
				break;
			}
			else if(rule == Rule::atom && isAtom(token))
			{
				semanticStack.push(token);
				token = m_lexer.nextToken();
			}
			else
			{
				throw CompilerException("Neočekavany token");
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
		throw CompilerException("Neočekávaný konec parsování");
	}
}
