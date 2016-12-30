#include "../../include/StdLib/BiggerThan.h"
#include "../../include/CompilerException.h"

BiggerThan::BiggerThan()
{
    m_args.push_back("a");
    m_args.push_back("b");
}

Token BiggerThan::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& a = copy.at("a");
    Token& b = copy.at("b");
    if(a.type != TokenType::NUMBER)
    {
        throw InterpreterException("Hodnota není číslo", a);
    }
    if(b.type != TokenType::NUMBER)
    {
        throw InterpreterException("Hodnota není číslo", a);
    }
    return Token{
        TokenType::BOOL,
        boost::get<float>(a.value) > boost::get<float>(b.value),
        std::move(a.filePos)
    };
}
