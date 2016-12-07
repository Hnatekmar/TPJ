#include "../include/Parser.h"
#include <cassert>
#include <stack>
#include <functional>

typedef std::function<Token(std::vector<std::shared_ptr<AST>>, Context&)> MirageFn;

#define MIRAGE_FN_HEAD Token{ \
		TokenType::FUNCTION, \
			static_cast<MirageFn>([](std::vector<std::shared_ptr<AST>> representation, Context& context){ \
					assert(representation.size() >= 1);
#define MIRAGE_FN_FOOTER }), \
		{} \
	}


Parser::Parser(Lexer& lexer) :	m_lexer(lexer),
				m_constants()
{
	m_constants["definuj"] = MIRAGE_FN_HEAD
						if(representation.size() != 3)
						{
							throw CompilerException("Funkce definuj přebírá 2 argumenty.", representation.front()->value);
						}
						auto what = representation.at(1)->value; // Identifikátor, který nahradí hodnotu
						if(what.type != TokenType::IDENTIFIER)
						{
							throw CompilerException("Definuj potřebuje validní identifikátor", representation.front()->evaluate(context));
							
						}
						context[boost::get<std::string>(what.value)] = representation.at(2)->evaluate(context);
						return context[boost::get<std::string>(what.value)];
					MIRAGE_FN_FOOTER;

	m_constants["neguj"] = MIRAGE_FN_HEAD
				if(representation.size() != 2)
				{
					throw CompilerException("Neguj bere jednu logickou hodnotu!", representation.at(1)->value);
				}
				auto value = representation.at(1)->evaluate(context);
				return Token{TokenType::BOOL, static_cast<bool>(!boost::get<bool>(value.value)), representation.at(0)->value.filePos};
				MIRAGE_FN_FOOTER;

	m_constants["a"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("a bere jednu logickou hodnotu!", representation.at(1)->value);
				}
				bool result = true;

				for(size_t i = 1; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::BOOL)
					{
						throw CompilerException("a bere pouze logické hodnoty!", value);
					}
					result = result && boost::get<bool>(value.value);
					if(!result)
					{
						break;
					}
				}
				return Token{TokenType::BOOL, static_cast<bool>(result), representation.at(0)->value.filePos};
				MIRAGE_FN_FOOTER;

	m_constants["nebo"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("nebo bere alespoň jednu logickou hodnotu!", representation.at(1)->value);
				}
				bool result = false;

				for(size_t i = 1; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::BOOL)
					{
						throw CompilerException("nebo bere pouze logické hodnoty!", value);
					}
					result = result || boost::get<bool>(value.value);
					if(result)
					{
						break;
					}
				}
				return Token{TokenType::BOOL, static_cast<bool>(result), representation.at(0)->value.filePos};
				MIRAGE_FN_FOOTER;

	m_constants["chyba"] = MIRAGE_FN_HEAD
					auto value = representation.at(1)->evaluate(context);
					throw CompilerException("Kritická chyba", value);
					return Token{};
				MIRAGE_FN_FOOTER;

	m_constants["list"] = MIRAGE_FN_HEAD
					std::list<Token> result;
					for(size_t i = 1; i < representation.size(); i++)
					{
						result.push_back(representation.at(i)->evaluate(context));
					}
					return Token{
						TokenType::LIST,
						result,
						representation.at(0)->value.filePos
					};
					MIRAGE_FN_FOOTER;
	
	m_constants["prvni"] = MIRAGE_FN_HEAD
					if(representation.size() != 2)
					{
						throw CompilerException("Funkce bere jeden argument typu list", representation.at(0)->evaluate(context));
					}
					auto value = representation.at(1)->evaluate(context);
					if(value.type != TokenType::LIST)
					{
						throw CompilerException("Funkce prvni bere jeden argument, který musí být typu list!", value);
					}
					auto list = boost::get<std::list<Token>>(value.value);
					return list.front();
				MIRAGE_FN_FOOTER;

	m_constants["zbytek"] = MIRAGE_FN_HEAD
					if(representation.size() != 2)
					{
						throw CompilerException("Funkce bere jeden argument typu list", representation.at(0)->evaluate(context));
					}
					auto value = representation.at(1)->evaluate(context);
					if(value.type != TokenType::LIST)
					{
						throw CompilerException("Funkce zbytek bere jeden argument, který musí být typu list!", value);
					}
					auto list = boost::get<std::list<Token>>(value.value);
					return Token{ 
						 TokenType::LIST,
						 std::list<Token>(std::next(list.begin()), list.end()),
						 representation.at(0)->value.filePos
					};
				MIRAGE_FN_FOOTER;
	
	m_constants["pridejDozadu"] = MIRAGE_FN_HEAD
					if(representation.size() != 3)
					{
						throw CompilerException("Funkce bere dva argumenty. List a hodnota.", representation.at(0)->evaluate(context));
					}
					auto value = representation.at(1)->evaluate(context);
					if(value.type != TokenType::LIST)
					{
						throw CompilerException("Argument musí být typu list!", value);
					}
					auto list = boost::get<std::list<Token>>(value.value);
					std::list<Token> newList(list.begin(), list.end());
					newList.push_back(representation.at(2)->evaluate(context));
					return Token{
						TokenType::LIST,
						newList,
						representation.at(0)->value.filePos
					};
				MIRAGE_FN_FOOTER;

	m_constants["pridejDopredu"] = MIRAGE_FN_HEAD
					if(representation.size() != 3)
					{
						throw CompilerException("Funkce bere dva argumenty. List a hodnota.", representation.at(0)->evaluate(context));
					}
					auto value = representation.at(1)->evaluate(context);
					if(value.type != TokenType::LIST)
					{
						throw CompilerException("Argument musí být typu list!", value);
					}
					auto list = boost::get<std::list<Token>>(value.value);
					std::list<Token> newList(list.begin(), list.end());
					newList.push_front(representation.at(2)->evaluate(context));
					return Token{
						TokenType::LIST,
						newList,
						representation.at(0)->value.filePos
					};
				MIRAGE_FN_FOOTER;
	
	m_constants["velikost"] = MIRAGE_FN_HEAD
					if(representation.size() != 2)
					{
						throw CompilerException("Funkce bere jeden argument typu list.", representation.at(0)->evaluate(context));
					}
					auto value = representation.at(1)->evaluate(context);
					if(value.type != TokenType::LIST)
					{
						throw CompilerException("Argument musí být typu list!", value);
					}
					auto list = boost::get<std::list<Token>>(value.value);
					return Token{
						TokenType::NUMBER,
						static_cast<float>(list.size()),
						representation.at(0)->value.filePos
					};
				MIRAGE_FN_FOOTER;

	m_constants["*"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("* bere alespoň jeden argument!", representation.at(0)->value);
				}
				float product = 1.0f;
				for(size_t i = 1; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::NUMBER)
					{
						throw CompilerException("* bere pouze čísla!", value);
					}
					product *= boost::get<float>(value.value);
					if(product == 0.0f)
					{
						break;
					}
				}
				return Token{TokenType::NUMBER, static_cast<float>(product), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;
	
	m_constants["funkce"] = MIRAGE_FN_HEAD
					if(representation.size() < 3)
					{
						throw CompilerException("Funkce potřebuje minimálně neprázdný seznam argumentů a tělo, které obsahuje minimálně jeden výraz!", representation.at(0)->value);
					}
	return Token{
						TokenType::FUNCTION,
						static_cast<MirageFn>([=](std::vector<std::shared_ptr<AST>> args, Context& ctx)
						{
							auto arglist = representation.at(1)->children;
							Context contextCopy = ctx;
							contextCopy.insert(context.begin(), context.end());
							if(args.size() - 1 != arglist.size())
							{
								throw CompilerException("Neplatný počet argumentů", args.at(0)->value);
							}
							for(size_t i = 0; i < arglist.size(); i++)
							{
								arglist.at(i)->call = false;
								if(arglist.at(i)->value.type != TokenType::IDENTIFIER)
								{
									throw CompilerException("V argumentech musí být pouze identifikátory", arglist.at(i)->value);
								}
								contextCopy[boost::get<std::string>(arglist.at(i)->value.value)] = args.at(i + 1)->evaluate(ctx);
							}
							for(size_t i = 2; i < representation.size() - 1; i++)
							{
								representation.at(i)->evaluate(contextCopy);
							}
							return representation.back()->evaluate(contextCopy);
						}),
						representation.at(0)->value.filePos
					};
				MIRAGE_FN_FOOTER;
	
	m_constants["/"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("* bere alespoň jeden argument!", representation.at(0)->value);
				}
				float product = 1.0f;
				auto first = representation.at(1)->evaluate(context);
				if(first.type != TokenType::NUMBER)
				{
					throw CompilerException("* bere pouze čísla!", first);
				}
				product = boost::get<float>(first.value);
				for(size_t i = 2; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::NUMBER)
					{
						throw CompilerException("* bere pouze čísla!", value);
					}
					product /= boost::get<float>(value.value);
					if(product == 0.0f)
					{
						break;
					}
				}
				return Token{TokenType::NUMBER, static_cast<float>(product), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants[">"] = MIRAGE_FN_HEAD
				if(representation.size() != 3)
				{
					throw CompilerException("> bere přesně 2 argumenty!", representation.at(0)->value);
				}
				auto a = representation.at(1)->evaluate(context);
				auto b = representation.at(2)->evaluate(context);
				if(a.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", a);
				}
				if(b.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", b);
				}
				return Token{TokenType::BOOL, static_cast<bool>(boost::get<float>(a.value) > boost::get<float>(b.value)), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants["<"] = MIRAGE_FN_HEAD
				if(representation.size() != 3)
				{
					throw CompilerException("> bere přesně 2 argumenty!", representation.at(0)->value);
				}
				auto a = representation.at(1)->evaluate(context);
				auto b = representation.at(2)->evaluate(context);
				if(a.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", a);
				}
				if(b.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", b);
				}
				return Token{TokenType::BOOL, static_cast<bool>(boost::get<float>(a.value) < boost::get<float>(b.value)), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants[">="] = MIRAGE_FN_HEAD
				if(representation.size() != 3)
				{
					throw CompilerException("> bere přesně 2 argumenty!", representation.at(0)->value);
				}
				auto a = representation.at(1)->evaluate(context);
				auto b = representation.at(2)->evaluate(context);
				if(a.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", a);
				}
				if(b.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", b);
				}
				return Token{TokenType::BOOL, static_cast<bool>(boost::get<float>(a.value) >= boost::get<float>(b.value)), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants["<="] = MIRAGE_FN_HEAD
				if(representation.size() != 3)
				{
					throw CompilerException("> bere přesně 2 argumenty!", representation.at(0)->value);
				}
				auto a = representation.at(1)->evaluate(context);
				auto b = representation.at(2)->evaluate(context);
				if(a.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", a);
				}
				if(b.type != TokenType::NUMBER)
				{
					throw CompilerException("První argument není číslo", b);
				}
				return Token{TokenType::BOOL, static_cast<bool>(boost::get<float>(a.value) <= boost::get<float>(b.value)), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants["+"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("+ bere alespoň jeden argument!", representation.at(0)->value);
				}
				float sum = 0.0f;
				for(size_t i = 1; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::NUMBER)
					{
						throw CompilerException("+ bere pouze čísla!", value);
					}
					sum += boost::get<float>(value.value);
				}
				return Token{TokenType::NUMBER, static_cast<float>(sum), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants["-"] = MIRAGE_FN_HEAD
				if(representation.size() < 2)
				{
					throw CompilerException("- bere alespoň jeden argument!", representation.at(0)->value);
				}
				auto value = representation.at(1)->evaluate(context);
				float sum = boost::get<float>(value.value);
				if(representation.size() == 2)
				{
					sum = -sum;
				}
				for(size_t i = 2; i < representation.size(); i++)
				{
					auto value = representation.at(i)->evaluate(context);
					if(value.type != TokenType::NUMBER)
					{
						throw CompilerException("* bere pouze čísla!", value);
					}
					sum -= boost::get<float>(value.value);
				}
				return Token{TokenType::NUMBER, static_cast<float>(sum), representation.at(0)->value.filePos};
			MIRAGE_FN_FOOTER;

	m_constants["pokud"] = MIRAGE_FN_HEAD
				if(representation.size() != 4)
				{
						throw CompilerException("pokud bere 3 argumenty", representation.at(0)->value);
				}
				auto assertion = representation.at(1)->evaluate(context);
				if(assertion.type != TokenType::BOOL)
				{
					throw CompilerException("První argument musí být logická hodnota", assertion);
				}
				if(boost::get<bool>(assertion.value))
				{
					return representation.at(2)->evaluate(context);
				}
				else
				{
					return representation.at(3)->evaluate(context);
				}
			MIRAGE_FN_FOOTER;
	
	m_constants["="] = MIRAGE_FN_HEAD
			if(representation.size() != 3)
			{
				throw CompilerException("= bere 2 argumenty, které porovná", representation.at(0)->evaluate(context));
			}
			auto a = representation.at(1)->evaluate(context);
			auto b = representation.at(2)->evaluate(context);
			if(a.type != b.type)
			{
				throw CompilerException("Nelze porovnávat argumenty rozdílných typů", b);
			}
			if(a.type == TokenType::STRING)
			{
				return Token{
					TokenType::BOOL,
					static_cast<bool>(boost::get<std::string>(a.value) == boost::get<std::string>(b.value)),
					representation.at(0)->evaluate(context).filePos
				};
			}
			if(a.type == TokenType::NUMBER)
			{
				return Token{
					TokenType::BOOL,
					static_cast<bool>(boost::get<float>(a.value) == boost::get<float>(b.value)),
					representation.at(0)->evaluate(context).filePos
				};
			}
			if(a.type == TokenType::BOOL)
			{
				return Token{
					TokenType::BOOL,
					static_cast<bool>(boost::get<bool>(a.value) == boost::get<bool>(b.value)),
					representation.at(0)->evaluate(context).filePos
				};
			}
			throw CompilerException("Nelze porovnávat argumenty rozdílných typů", representation.at(0)->value);
			MIRAGE_FN_FOOTER;
}

void Parser::parse()
{
	std::stack<Rule> stack;
	stack.push(Rule::END_OF_PROGRAM);
	stack.push(Rule::Start);
	Token token = m_lexer.nextToken();
	auto rule = stack.top();
	std::shared_ptr<AST> ast(nullptr);
	while(!stack.empty())
	{
		rule = stack.top();
		stack.pop();
		if(rule == Rule::SCall)
		{
			assert(ast != nullptr);
			std::cout << "Hodnota výrazu: " << ast->evaluate(m_constants) << std::endl;
			ast = nullptr;
		}
		else if(isTerminal(rule))
		{
			if(rule == Rule::L_PAREN && token.type == TokenType::L_PAREN)
			{
				token = m_lexer.nextToken();
				std::shared_ptr<AST> tmpAST(new AST(token, ast, true));
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
				token = m_lexer.nextToken();
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
				std::shared_ptr<AST> tmpAST(new AST(token, ast, false));
				assert(ast != nullptr);
				ast->children.push_back(tmpAST);
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
