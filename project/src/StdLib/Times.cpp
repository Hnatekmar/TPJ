#include "../../include/StdLib/Times.h"
#include "../../include/CompilerException.h"

Times::Times()
{
    m_args.push_back("...");
}

Token Times::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    std::list<Token>& list = boost::get<std::list<Token>>(copy.at("...").value);
    auto it = list.begin();
    if((*it).type != TokenType::NUMBER)
    {
        throw InterpreterException("Není číslo", *it);
    }
    float product = boost::get<float>((*it).value);
    it++;
    while(it != list.end())
    {
        if((*it).type != TokenType::NUMBER)
        {
            throw InterpreterException("Není číslo", *it);
        }
        product = product * boost::get<float>((*it).value);
        it++;
    }
    return Token{
        TokenType::NUMBER,
        std::move(product),
        std::move(copy.at("...").filePos)
    };
}
