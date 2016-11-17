#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Lexer.h"
#include "AST.h"
#include "CompilerException.h"
#include <list>

/**
 * S -> Expression
 * Expression -> atom
 * Expression -> ( EArgs )
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
		epsilon
	};
	
	std::map<Rule, std::map<TokenType, std::list<Rule> > > m_parsingTable = { 
		{
			{
				Rule::Start,
				{
					{
						TokenType::IDENTIFIER,
						{
							Rule::Expression
						}
					},
					{
						TokenType::NUMBER,
						{
							Rule::Expression
						}
					},
					{
						TokenType::STRING,
						{
							Rule::Expression
						}
					},
					{ 
						TokenType::L_PAREN,
						{
							Rule::Expression
						}
					}
				}
			},
			{
				Rule::Expression,
				{
					{
						TokenType::STRING,
						{
							Rule::atom
						}
					},
					{
						TokenType::IDENTIFIER,
						{
							Rule::atom
						}
					},
					{
						TokenType::NUMBER,
						{
							Rule::atom
						}
					},
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
							Rule::Expression,
							Rule::EArgs
						}
					},
					{
						TokenType::IDENTIFIER,
						{
							Rule::Expression,
							Rule::EArgs
						}
					},
					{
						TokenType::STRING,
						{
							Rule::Expression,
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

	bool isTerminal(const Rule& rule)
	{
		return rule != Rule::Start && rule != Rule::EArgs && rule != Rule::Expression;
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

	Lexer& m_lexer;

	void except(TokenType type);
	public:
		Parser(Lexer& lexer);
		void parse();
};

#endif
