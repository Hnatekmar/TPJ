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


/**
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
        PROGRAM,
        EXPRESSION,
        EXPRESSION2,
        ARGUMENT,
        EXPANSION,
        ATOM,
        L_PAREN,
		R_PAREN,
        S_CALL,
        EPSILON,
        END_OF_PROGRAM,
        EXPANSION_NAME,
        BUILD_TREE
    };

    std::map<TokenType, std::string> m_tokenTypeToString = {
        { TokenType::BOOL, "logická hodnota" },
        { TokenType::END_OF_PROGRAM, "EOF (konec programu)" },
        { TokenType::IDENTIFIER, "identifikátor" },
        { TokenType::L_PAREN, "levá závorka" },
        { TokenType::R_PAREN, "pravá závorka" },
        { TokenType::STRING, "řetězec" },
        { TokenType::EXPANSION, "expanze" },
        { TokenType::NUMBER, "číslo" }
    };

    std::map<Rule, std::string> m_ruleToString = {
        { Rule::PROGRAM, "Začátek" },
        { Rule::EXPRESSION, "výraz (..." },
        { Rule::EXPRESSION2, "výraz ... nebo )" },
        { Rule::ARGUMENT, "argument" },
        { Rule::L_PAREN, "Závorka (" },
        { Rule::R_PAREN, "Závorka )" },
        { Rule::ATOM, "atom (číslo, řetězec, identifikátor)" },
        { Rule::EPSILON, "cokoliv" },
        { Rule::S_CALL, "Volání/aplikace (výraz ve tvaru (...))" },
        { Rule::END_OF_PROGRAM, "konec programu" }
    };
	Context m_constants;

    std::map<Rule, std::map<TokenType, std::list<Rule> > > m_parsingTable =
    {
            {
                    Rule::PROGRAM,
                    {
                            {
                                    TokenType::L_PAREN,
                                    {
                                            Rule::EXPRESSION,
                                            Rule::S_CALL,
                                            Rule::PROGRAM
                                    }
                            },
                            {
                                    TokenType::EXPANSION,
                                    {
                                            Rule::EXPANSION,
                                            Rule::S_CALL,
                                            Rule::PROGRAM
                                    }
                            },
                            {
                                    TokenType::END_OF_PROGRAM,
                                    {
                                            Rule::EPSILON
                                    }
                            }
                    }
            },
            {
                    Rule::EXPRESSION,
                    {
                            {
                                    TokenType::L_PAREN,
                                    {
                                            Rule::L_PAREN,
                                            Rule::EXPRESSION2,
                                            Rule::BUILD_TREE
                                    }
                            },
                            {
                                    TokenType::EXPANSION,
                                    {
                                            Rule::EXPANSION,
                                            Rule::BUILD_TREE
                                    }
                            }
                    }
            },
            {
                    Rule::EXPRESSION2,
                    {
                            {
                                    TokenType::L_PAREN,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            },
                            {
                                    TokenType::R_PAREN,
                                    {
                                            Rule::R_PAREN
                                    }
                            },
                            {
                                    TokenType::BOOL,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            },
                            {
                                    TokenType::IDENTIFIER,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            },
                            {
                                    TokenType::STRING,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            },
                            {
                                    TokenType::NUMBER,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            },
                            {
                                    TokenType::EXPANSION,
                                    {
                                            Rule::ARGUMENT,
                                            Rule::EXPRESSION2
                                    }
                            }
                    }
            },
            {
                    Rule::ARGUMENT,
                    {
                            {
                                    TokenType::L_PAREN,
                                    {
                                            Rule::EXPRESSION
                                    }
                            },
                            {
                                    TokenType::BOOL,
                                    {
                                            Rule::ATOM
                                    }
                            },
                            {
                                    TokenType::IDENTIFIER,
                                    {
                                            Rule::ATOM
                                    }
                            },
                            {
                                    TokenType::STRING,
                                    {
                                            Rule::ATOM
                                    }
                            },
                            {
                                    TokenType::NUMBER,
                                    {
                                            Rule::ATOM
                                    }
                            },
                            {
                                    TokenType::EXPANSION,
                                    {
                                            Rule::EXPRESSION
                                    }
                            }
                    }
            },
            {
                    Rule::EXPANSION,
                    {
                            {
                                    TokenType::EXPANSION,
                                    {
                                            Rule::EXPANSION_NAME,
                                            Rule::ARGUMENT
                                    }
                            }
                    }
            }
    };

	Token evaluate(std::shared_ptr<AST>& ast, Context& context);

	Token getValue(Token token, Context& context);

	// Pokusí se zavolat funkci
	Token sCall(std::shared_ptr<AST>& ast, Context& context);

	bool isTerminal(const Rule& rule)
	{
        return rule != Rule::S_CALL &&
               rule != Rule::PROGRAM &&
               rule != Rule::EXPANSION &&
               rule != Rule::EXPRESSION &&
               rule != Rule::ARGUMENT &&
               rule != Rule::EXPRESSION2;
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
		       token.type == TokenType::IDENTIFIER ||
		       token.type == TokenType::BOOL;
	}


	void except(TokenType type);
	public:
        Parser();
        void parse(Lexer& lexer, bool printExpression = false);
};

#endif
