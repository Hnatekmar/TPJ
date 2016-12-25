#include "../../include/StdLib/Plus.h"
#include "../../include/CompilerException.h"

Plus::Plus()
{
    m_args.push_back("...");
}

Token Plus::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    std::list<Token>& list = boost::get<std::list<Token>>(copy.at("...").value);
    auto it = list.begin();
    if((*it).type != TokenType::NUMBER)
    {
        throw InterpreterException("Není číslo", *it);
    }
    float sum = boost::get<float>((*it).value);
    it++;
    while(it != list.end())
    {
        if((*it).type != TokenType::NUMBER)
        {
            throw InterpreterException("Není číslo", *it);
        }
        sum = sum + boost::get<float>((*it).value);
        it++;
    }
    return Token{
        TokenType::NUMBER,
        std::move(sum),
        std::move(copy.at("...").filePos)
    };
}
