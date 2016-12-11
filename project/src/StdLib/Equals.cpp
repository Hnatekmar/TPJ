#include "../../include/StdLib/Equals.h"

#include "../../include/CompilerException.h"

Token Equals::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    if(args.size() != 3)
    {
        throw InterpreterException("= bere 2 argumenty, které porovná", args.at(0)->evaluate(context));
    }
    auto a = args.at(1)->evaluate(context);
    auto b = args.at(2)->evaluate(context);
    if(a.type != b.type)
    {
        throw InterpreterException("Nelze porovnávat argumenty rozdílných typů", b);
    }
    if(a.type == TokenType::STRING)
    {
        return Token{
            TokenType::BOOL,
                            static_cast<bool>(boost::get<std::string>(a.value) == boost::get<std::string>(b.value)),
                            args.at(0)->evaluate(context).filePos
        };
    }
    if(a.type == TokenType::NUMBER)
    {
        return Token{
            TokenType::BOOL,
                            static_cast<bool>(boost::get<float>(a.value) == boost::get<float>(b.value)),
                            args.at(0)->evaluate(context).filePos
        };
    }
    if(a.type == TokenType::BOOL)
    {
        return Token{
            TokenType::BOOL,
                            static_cast<bool>(boost::get<bool>(a.value) == boost::get<bool>(b.value)),
                            args.at(0)->evaluate(context).filePos
        };
    }
    throw InterpreterException("Nelze porovnávat argumenty rozdílných typů", args.at(0)->value);
}
