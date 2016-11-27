#include "../include/Parser.h"
#include <cassert>
#include <stack>

Parser::Parser(Lexer& lexer) :	m_lexer(lexer),
				m_constants()
{
	m_constants["tiskni"] = Token{ // Debugovací funkce, která je zde dočasně!
		TokenType::FUNCTION,
		[&](Context& context, std::list<std::shared_ptr<AST>>& arguments)
		{
			for(auto node : arguments)
			{
				auto value = evaluate(node, context);
				std::cout << value << " ";
			}
			std::cout << std::endl;
			return Token{};
		},
		{}
	};
	m_constants["list"] = Token{ // Debugovací funkce, která je zde dočasně!
		TokenType::FUNCTION,
			[&](Context& context, std::list<std::shared_ptr<AST>>& arguments)
			{
				std::list<Token> list;
				for(auto node : arguments)
				{
					auto value = evaluate(node, context);
					list.push_back(value);
				}
				return Token{TokenType::LIST, list, {}};
			},
			{}
	};
	
	/*
	m_constants["lambda"] = Token{
		TokenType::FUNCTION,
		[&](Context& context, std::list<std::shared_ptr<AST>>& arguments)
		{
			return Token{
					// (lambda () (* x y z))
					TokenType::FUNCTION,
					[arguments=, this&](Context& ctx, std::list<std::shared_ptr<AST>>& args)
					{
						if(args.size() < 2)
						{
							throw CompilerException("Funkce musí mít alespoň 2 argumenty první je list argumentů a druhý tělo funkce", {});
						}
						Context ctxCopy = ctx;
						return Token{};
					},
				{}
			};
		},
		{}
	};
	*/
	m_constants["definuj"] = Token{ // Debugovací funkce, která je zde dočasně!
		TokenType::FUNCTION,
		[&](Context& context, std::list<std::shared_ptr<AST>>& arguments)
		{
			if(arguments.size() != 2)
			{
				throw CompilerException("Definuj očekává 2 argumenty", {});
			}
			auto id = arguments.front()->value;
			if(id.type == TokenType::L_PAREN)
			{
				id = sCall(arguments.front(), context);
			}
			else if(id.type != TokenType::IDENTIFIER)
			{
				throw CompilerException("Definuj očekává výraz, který je přeložitelný na identifikátor", arguments.front()->value);
			}
			if(id.type == TokenType::IDENTIFIER)
			{
				context[boost::get<std::string>(id.value)] = evaluate(arguments.back(), context);
			}
			else
			{
				throw CompilerException("Definuj očekává výraz, který je přeložitelný na identifikátor", arguments.front()->value);
			}
			return Token{};
		},
		{}
	};
	m_constants["*"] = Token{
		TokenType::FUNCTION,
		[&](Context& context, std::list<std::shared_ptr<AST>>& arguments)
		{
			float product = 1.0f;
			for(auto node : arguments)
			{
				auto value = evaluate(node, context);
				if(value.type != TokenType::NUMBER)
				{
					throw CompilerException("Hodnota není číslo", value);
				}
				product *= boost::get<float>(node->value.value);
				if(product == 0.0f)
				{
					break;
				}
			}
			return Token{TokenType::NUMBER, product, {}};
		},
		{}};
}

Token Parser::evaluate(std::shared_ptr<AST>& ast, Context& context)
{
	if(isFunction(ast->value, context) || ast->value.type == TokenType::L_PAREN) // je funkce
	{
		return sCall(ast, context);
	}
	else
	{
		if(ast->value.type == TokenType::IDENTIFIER)
		{
			return getValue(ast->value, context);
		}
	}
	return ast->value;
}

Token Parser::getValue(Token token, Context& context)
{
	if(token.type == TokenType::IDENTIFIER)
	{
		while(token.type == TokenType::IDENTIFIER)
		{
			if(context.find(boost::get<std::string>(token.value)) != context.end())
			{
				token = context.at(boost::get<std::string>(token.value));
			}
			else
			{
				throw CompilerException("Nelze přeložit symbol", token);
			}
		}
		return token;
	}
	else
	{
		return token;
	}
}

Token Parser::sCall(std::shared_ptr<AST>& ast, Context& context)
{
	Token id = ast->value;
	if(id.type == TokenType::L_PAREN)
	{
		/**
		 * Strom není ve správnem formátu toto se stává pokud máme výraz jako například
		 * ((l 0 1) 5)
		 * Vyprodukované ast, pak vypadá následovně
		 *           (
		 *          / \
		 *   [l 0 1]   5
		 * Aby by byl výraz vyhodnotitelný je potřeba nejdřív zjistit hodnotu (l 0 1)
		 * Proto vytvoříme nový uzel, který jej reprezentuje. Vyhodnotíme jej a pokud je jeho hodnota funkce, tak ji aplikujeme.
		 */
		if(ast->children.size() == 0)
		{
			throw CompilerException("Volání ( nemá žádnou hodnotu. Tedy ho nelze provést!", ast->value);
		}
		std::shared_ptr<AST> newNode(new AST(ast->children.front()->value, ast));
		newNode->children.insert(newNode->children.begin(), std::next(ast->children.begin()), ast->children.end());
		id = sCall(newNode, context);
	}
	if(id.type == TokenType::IDENTIFIER)
	{
		id = getValue(id, m_constants);
	}
	if(id.type != TokenType::FUNCTION)
	{
		throw CompilerException("Token není funkce!", id);
	}
	return boost::get<std::function<Token(Context& context, std::list<std::shared_ptr<AST>>&)>>(id.value)(context, ast->children);
}

void Parser::parse()
{
	std::stack<Rule> stack;
	stack.push(Rule::END_OF_PROGRAM);
	stack.push(Rule::Start);
	Token token = m_lexer.nextToken();
	auto rule = stack.top();
	std::shared_ptr<AST> ast = nullptr;
	while(!stack.empty())
	{
		rule = stack.top();
		stack.pop();
		if(rule == Rule::SCall)
		{
			sCall(ast, m_constants);
			ast = nullptr;
		}
		else if(isTerminal(rule))
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				token = m_lexer.nextToken();
				std::shared_ptr<AST> newAST(new AST(token, ast));
				newAST->value.type = TokenType::END_OF_PROGRAM;
				if(token.type == TokenType::R_PAREN)
				{
					newAST->value.value = std::string("list");
				}
				if(ast != nullptr)
				{
					ast->children.push_back(newAST);
				}
				ast = newAST;
			}
			else if(rule == Rule::epsilon)
			{
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
				ast->value.type = TokenType::IDENTIFIER;
				token = m_lexer.nextToken();
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
				if(ast->value.type == TokenType::IDENTIFIER)
				{
					std::shared_ptr<AST> child(new AST(token, ast));
					ast->children.push_back(child);
				}
				else
				{
					ast->value.type = TokenType::IDENTIFIER;
				}
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
