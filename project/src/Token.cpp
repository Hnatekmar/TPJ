#include "../include/Token.h"

std::ostream& operator<<(std::ostream& stream, const Token& token)
{
	if(token.type == TokenType::L_PAREN)
	{
		stream << '(';
	}
	if(token.type == TokenType::R_PAREN)
	{
		stream << ')';
	}
	if(token.type == TokenType::IDENTIFIER)
	{
		stream << boost::get<std::string>(token.value);
	}
	if(token.type == TokenType::NUMBER)
	{
		stream << boost::get<float>(token.value);
	}
	if(token.type == TokenType::STRING)
	{
		stream << boost::get<std::string>(token.value);
	}
	if(token.type == TokenType::FUNCTION)
	{
		stream << "<funkce>";
	}
	if(token.type == TokenType::BOOL)
	{
		stream << (boost::get<bool>(token.value) ? "PRAVDA" : "NEPRAVDA");
	}
	if(token.type == TokenType::LIST)
	{
        auto list = boost::get<List<Token>>(token.value);
        stream << '(';
        while(!list.empty())
        {
            if(!list.empty())
            {
                stream << list.first();
                if(!list.rest().empty())
                {
                    stream << ' ';
                }
            }
            list = list.rest();
		}
        stream << ')';
    }
    if(token.type == TokenType::GRAPHICS_ELEMENT)
    {
        stream << boost::get<std::shared_ptr<GraphicsObject> >(token.value)->toString();
    }
    if(token.type == TokenType::MACRO_FN)
    {
        stream << "<makro>";
    }
	if(token.type == TokenType::END_OF_PROGRAM)
	{
		stream << "EOF";
    }
    if(token.type == TokenType::EXPANSION)
    {
        stream << boost::get<std::string>(token.value);
    }
	return stream;
}
