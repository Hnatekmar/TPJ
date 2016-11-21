#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Lexer.h"
#include "AST.h"
#include "CompilerException.h"
#include <list>
#include <functional>
#include <deque>

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
	std::map<std::string, std::function<void (std::deque<Token>&)> > m_functions = 
	{
		{
			"tiskni", // Pro debugovací účely z finální verze je třeba ji odstranit
			{
				[&](std::deque<Token>& tokens)
				{
					while(!tokens.empty())
					{
						auto token = tokens.front();
						if(token.type == TokenType::L_PAREN)
						{
							sCall(tokens);
							continue;
						}
						else if(token.type == TokenType::IDENTIFIER)
						{
							if(m_constants.find(boost::get<std::string>(token.value)) != m_constants.end())
							{
								auto newToken = m_constants.at(boost::get<std::string>(token.value));

								tokens.pop_front();
								tokens.push_front(newToken);
								continue;
							}
							else
							{
								throw CompilerException("Neplatný identifikátor");
							}
						}
						else if(token.type == TokenType::R_PAREN)
						{
							tokens.pop_front();
							break;
						}
						std::cout << token.value << " ";
						tokens.pop_front();
					}
					std::cout << std::endl;
				}
			}
		},
		{
			"definuj",
			[&](std::deque<Token>& tokens)
			{
				if(tokens.empty())
				{
					throw CompilerException("Žádne argumenty pro definuj");
				}
				auto constantName = tokens.front();
				if(constantName.type != TokenType::IDENTIFIER)
				{
					throw CompilerException("Neplatný argument pro definuj. Očekával jsem identifikátor");
				}
				tokens.pop_front();
				if(tokens.empty())
				{
					throw CompilerException("Nemám co přiřadit do " + boost::get<std::string>(constantName.value));
				}
				if(tokens.front().type == TokenType::L_PAREN)
				{
					sCall(tokens);
				}
				m_constants[boost::get<std::string>(constantName.value)] = tokens.front();
				tokens.pop_front();
			}
		},
		{
			"*",
			[&](std::deque<Token>& tokens) {
				double product = 1.0;
				if(tokens.empty())
				{
					throw CompilerException("Žádne argumenty pro *");
				}
				while(!tokens.empty())
				{
					auto token = tokens.front();
					if(token.type == TokenType::L_PAREN)
					{
						sCall(tokens);
						continue;
					}
					else if(token.type == TokenType::R_PAREN)
					{
						tokens.pop_front();
						break;
					}
					else if(token.type == TokenType::IDENTIFIER)
					{
						if(m_constants.find(boost::get<std::string>(token.value)) != m_constants.end())
						{
							auto newToken = m_constants.at(boost::get<std::string>(token.value));

							tokens.pop_front();
							tokens.push_front(newToken);
							continue;
						}
						else
						{
							throw CompilerException("Neplatný identifikátor");
						}
					}
					product *= boost::get<double>(token.value);
					tokens.pop_front();
				}
				tokens.push_front({TokenType::NUMBER, product});
			}
		}
	};

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

	void sCall(std::deque<Token>& semanticDeque);

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

	Lexer& m_lexer;

	void except(TokenType type);
	public:
		Parser(Lexer& lexer);
		void parse();
};

#endif
