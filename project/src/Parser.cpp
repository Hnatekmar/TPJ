#include "../include/Parser.h"
#include <cassert>
#include <stack>

Parser::Parser(Lexer& lexer) :	m_lexer(lexer),
				m_constants()
{
	m_constants["tiskni"] = Token{ // Debugovací funkce, která je zde dočasně!
		TokenType::FUNCTION,
		[&](Context context, std::list<std::shared_ptr<AST>>& arguments)
		{
			for(auto node : arguments)
			{
				if(node->value.type == TokenType::IDENTIFIER)
				{
					auto value = sCall(node);
					std::cout << value << " ";
				}
				else
				{
					std::cout << node->value << " ";
				}
			}
			std::cout << std::endl;
			return Token{};
		},
		{}};
	m_constants["*"] = Token{
		TokenType::FUNCTION,
		[&](Context context, std::list<std::shared_ptr<AST>>& arguments)
		{
			float product = 1.0f;
			for(auto node : arguments)
			{
				if(node->value.type == TokenType::IDENTIFIER)
				{
					auto value = sCall(node);
					if(value.type != TokenType::NUMBER)
					{
						throw CompilerException("Hodnota není číslo", value);
					}
					product *= boost::get<float>(value.value);
				}
				else if(node->value.type != TokenType::NUMBER)
				{
					if(node->value.type == TokenType::IDENTIFIER)
					{
						auto token = getValue(node->value, context);
						if(token.type != TokenType::NUMBER)
						{
							throw CompilerException("Hodnota není číslo", token);
						}
						product *= boost::get<float>(token.value);
					}
				}
				else
				{
					product *= boost::get<float>(node->value.value);
				}
				if(product == 0.0f)
				{
					break;
				}
			}
			return Token{TokenType::NUMBER, product, {}};
		},
		{}};
}

Token Parser::getValue(Token token, Context& context)
{
	assert(token.type == TokenType::IDENTIFIER);
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

Token Parser::sCall(std::shared_ptr<AST>& ast)
{
	Token id;
	if(ast->value.type == TokenType::L_PAREN)
	{
		id = sCall(ast->children.back());
	}
	id = ast->value;
	if(id.type == TokenType::IDENTIFIER)
	{
		id = getValue(id, m_constants);
	}
	if(id.type != TokenType::FUNCTION)
	{
		throw CompilerException("Token není funkce!", id);
	}
	return boost::get<std::function<Token(Context context, std::list<std::shared_ptr<AST>>&)>>(id.value)(m_constants, ast->children);
}

void Parser::parse()
{
	std::stack<Rule> stack;
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
			sCall(ast);
		}
		else if(rule == Rule::epsilon)
		{
		}
		else if(isTerminal(rule))
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				//semanticStack.push(token);
				token = m_lexer.nextToken();
				std::shared_ptr<AST> newAST(new AST(token, ast));
				if(ast != nullptr)
				{
					ast->children.push_back(newAST);
				}
				ast = newAST;
				token = m_lexer.nextToken();
			}
			else if(rule == Rule::R_PAREN && token.type == TokenType::R_PAREN)
			{
				token = m_lexer.nextToken();
				if(ast->root != nullptr)
				{
					ast = ast->root;
				}
			}
			else if(rule == Rule::END_OF_PROGRAM && token.type == TokenType::END_OF_PROGRAM)
			{
				assert(stack.empty());
				break;
			}
			else if(rule == Rule::atom && isAtom(token))
			{
				std::shared_ptr<AST> child(new AST(token, ast));
				ast->children.push_back(child);
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
