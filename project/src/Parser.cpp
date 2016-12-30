#include "../include/Parser.h"
#include <cassert>
#include <stack>
#include <functional>
#include "../include/StdLib/Define.h"
#include "../include/StdLib/Not.h"
#include "../include/StdLib/CreateFunction.h"
#include "../include/StdLib/Equals.h"
#include "../include/StdLib/And.h"
#include "../include/StdLib/Macro.h"
#include "../include/StdLib/Quote.h"
#include "../include/StdLib/Eval.h"
#include "../include/StdLib/If.h"
#include "../include/StdLib/Times.h"
#include "../include/StdLib/List.h"
#include "../include/StdLib/Import.h"
#include "../include/StdLib/First.h"
#include "../include/StdLib/AddFront.h"
#include "../include/StdLib/AddBack.h"
#include "../include/StdLib/Divide.h"
#include "../include/StdLib/Plus.h"
#include "../include/StdLib/Minus.h"
#include "../include/StdLib/Size.h"
#include "../include/StdLib/Rest.h"
#include "../include/StdLib/Or.h"
#include "../include/StdLib/Error.h"
#include "../include/StdLib/Debug.h"
#include "../include/StdLib/BiggerThan.h"
#include "../include/Graphics.h"
#include "../include/StdLib/CreateGraphicsElement.h"
#include "../include/StdLib/ToString.h"

Parser::Parser() :
				m_constants()
{
    m_constants["definuj"] = Token{
            TokenType::FUNCTION,
            std::make_shared<Define>(),
            {}
    };

    m_constants["neguj"] = Token{
            TokenType::FUNCTION,
            std::make_shared<Not>(),
            {}
    };

    m_constants["funkce"] = Token{
            TokenType::FUNCTION,
            std::make_shared<CreateFunction>(),
            {}
    };

    m_constants["="] = Token{
            TokenType::FUNCTION,
            std::make_shared<Equals>(),
            {}
    };

    m_constants["a"] = Token{
            TokenType::FUNCTION,
            std::make_shared<And>(),
            {}
    };

    m_constants["makro"] = Token{
        TokenType::FUNCTION,
        std::make_shared<CreateMacro>(),
        {}
    };

    m_constants["nevyhodnocuj"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Quote>(),
        {}
    };

    m_constants["vyhodnot"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Eval>(),
        {}
    };

    m_constants["pokud"] = Token{
         TokenType::MACRO_FN,
         std::make_shared<If>(),
         {}
    };

    m_constants["*"] = Token{
          TokenType::FUNCTION,
          std::make_shared<Times>(),
          {}
    };

    m_constants["/"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Divide>(),
        {}
    };

    m_constants["+"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Plus>(),
        {}
    };

    m_constants["-"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Minus>(),
        {}
    };

    m_constants["list"] = Token{
          TokenType::FUNCTION,
          std::make_shared<ListFn>(),
          {}
    };

    m_constants["importuj"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Import>(*this),
        {}
    };

    m_constants["prvni"] = Token{
        TokenType::FUNCTION,
        std::make_shared<First>(),
        {}
    };

    m_constants["pridejDopredu"] = Token{
        TokenType::FUNCTION,
        std::make_shared<AddFront>(),
        {}
    };

    m_constants["pridejDozadu"] = Token{
        TokenType::FUNCTION,
        std::make_shared<AddBack>(),
        {}
    };

    m_constants["velikost"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Size>(),
        {}
    };

    m_constants["zbytek"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Rest>(),
        {}
    };

    m_constants["nebo"] = Token{
        TokenType::MACRO_FN,
        std::make_shared<Or>(),
        {}
    };

    m_constants["chyba"] = Token{
        TokenType::FUNCTION,
        std::make_shared<Error>(),
        {}
    };

    m_constants["debuguj"] = Token{
         TokenType::FUNCTION,
         std::make_shared<Debug>(),
         {}
    };

    m_constants[">"] = Token{
         TokenType::FUNCTION,
         std::make_shared<BiggerThan>(),
         {}
    };

    m_constants["vykresli"] = Token{
         TokenType::FUNCTION,
         std::make_shared<Graphics>(),
         {}
    };

    m_constants["element"] = Token{
         TokenType::FUNCTION,
         std::make_shared<CreateGraphicsElement>(),
         {}
    };

    m_constants["hodnota->retezec"] = Token{
         TokenType::FUNCTION,
         std::make_shared<ToString>(),
         {}
    };
}

void Parser::parse(Lexer &lexer)
{
	std::stack<Rule> stack;
	stack.push(Rule::END_OF_PROGRAM);
	stack.push(Rule::Start);
    Token token = lexer.nextToken();
    Rule rule;
    std::shared_ptr<AST> ast(nullptr);
	while(!stack.empty())
	{
		rule = stack.top();
		stack.pop();
		if(rule == Rule::SCall)
		{
            assert(ast != nullptr);
            ast->evaluate(m_constants);
			ast = nullptr;
		}
		else if(isTerminal(rule))
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
                token = lexer.nextToken();
                std::shared_ptr<AST> tmpAST = std::make_shared<AST>(token, ast, true);
				if(ast != nullptr)
				{
					ast->children.push_back(tmpAST);
				}
				ast = tmpAST;
			}
			else if(rule == Rule::epsilon)
			{
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
                token = lexer.nextToken();
				assert(ast != nullptr);
				if(ast->root != nullptr)
				{
					ast = ast->root;
				}
			}
			else if(rule == Rule::END_OF_PROGRAM && token.type == TokenType::END_OF_PROGRAM)
			{
				break;
			}
			else if(rule == Rule::atom && isAtom(token))
			{
                std::shared_ptr<AST> tmpAST = std::make_shared<AST>(token, ast, false);
				assert(ast != nullptr);
				ast->children.push_back(tmpAST);
                token = lexer.nextToken();
			}
			else
			{
				throw InterpreterException("Neočekavany token", token);
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
			throw InterpreterException("Přepisovací pravidlo nenalezeno", token);
		}
	}
    if(!lexer.eof())
	{
        throw InterpreterException("Neočekávaný konec parsování", token);
	}
}
