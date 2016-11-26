#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Lexer.h"
#include "CompilerException.h"
#include "AST.h"
#include <list>
#include <functional>
#include <deque>
#include <map>

typedef std::map<std::string, Token> Context;

/**
 * SCall(semanticDeque) -> { // Sémantická akce volání
 *	assert(semanticDeque.pop() == '(');
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
 *
 * S -> Expression SCall S
 * S -> epsilon
 * Expression -> ( EArgs )
 * EArgs -> atom EArgs
 * EArgs -> Expression EArgs
 * EArgs -> epsilon
 */
class Parser
{
	enum class Rule
	{
		Start,
		Expression,
		EArgs,
		L_PAREN,
		R_PAREN,
		atom,
		epsilon,
		SCall,
		END_OF_PROGRAM
	};
	Lexer& m_lexer;
	std::map<Rule, std::string> m_ruleToString = {
		{ Rule::Start, "Start" },
		{ Rule::Expression, "Expression" },
		{ Rule::EArgs, "EArgs" },
		{ Rule::L_PAREN, "L_PAREN" },
		{ Rule::R_PAREN, "R_PAREN" },
		{ Rule::atom, "atom" },
		{ Rule::epsilon, "epsilon" },
		{ Rule::SCall, "SCall" },
		{ Rule::END_OF_PROGRAM, "END_OF_PROGRAM" }
	};
	std::map<std::string, Token> m_constants;

	std::map<Rule, std::map<TokenType, std::list<Rule> > > m_parsingTable = { 
		{
			{
				Rule::Start,
				{
					{
						TokenType::L_PAREN,
						{
							Rule::Expression,
							Rule::SCall,
							Rule::Start
						},
					},
					{
						TokenType::END_OF_PROGRAM,
						{
							Rule::END_OF_PROGRAM
						}
					}
				}
			},
			{
				Rule::Expression,
				{
					{
						TokenType::L_PAREN,
						{
							Rule::L_PAREN,
							Rule::EArgs,
							Rule::R_PAREN
						}
					}
				}
			},
			{
				Rule::EArgs,
				{
					{
						TokenType::NUMBER,
						{
							Rule::atom,
							Rule::EArgs
						}
					},
					{
						TokenType::IDENTIFIER,
						{
							Rule::atom,
							Rule::EArgs
						}
					},
					{
						TokenType::STRING,
						{
							Rule::atom,
							Rule::EArgs
						}
					},
					{
						TokenType::L_PAREN,
						{
							Rule::Expression,
							Rule::EArgs
						}
					},
					{
						TokenType::R_PAREN,
						{
							Rule::epsilon
						}
					}
				}
			}
		}
	};

	Token getValue(Token token, Context& context);

	// Pokusí se zavolat funkci
	Token sCall(std::shared_ptr<AST>& ast);

	bool isTerminal(const Rule& rule)
	{
		return rule != Rule::SCall && rule != Rule::Start && rule != Rule::EArgs && rule != Rule::Expression;
	}

	/**
	 * Zjístí, zda se dané pravidlo nachází v tabulce
	 */
	bool hasRule(Rule rule, TokenType type)
	{
		if(m_parsingTable.find(rule) != m_parsingTable.end())
		{
			if(m_parsingTable.at(rule).find(type) != m_parsingTable.at(rule).end())
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * Zjišťuje, zda je token atom.
	 */
	bool isAtom(const Token& token)
	{
		return token.type == TokenType::STRING ||
		       token.type == TokenType::NUMBER ||
		       token.type == TokenType::IDENTIFIER;
	}


	void except(TokenType type);
	public:
		Parser(Lexer& lexer);
		void parse();
};

#endif
