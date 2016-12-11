#include "../../include/StdLib/And.h"
#include "../../include/CompilerException.h"

Token And::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    if(args.size() < 2)
    {
        throw InterpreterException("a bere jednu logickou hodnotu!", args.at(1)->value);
    }
    bool result = true;

    for(size_t i = 1; i < args.size(); i++)
    {
        auto value = args.at(i)->evaluate(context);
        if(value.type != TokenType::BOOL)
        {
            throw InterpreterException("a bere pouze logické hodnoty!", value);
        }
        result = result && boost::get<bool>(value.value);
        if(!result)
        {
            break;
        }
    }
    return Token{TokenType::BOOL, static_cast<bool>(result), args.at(0)->value.filePos};
}
