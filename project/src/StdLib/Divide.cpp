#include "../../include/StdLib/Divide.h"
#include "../../include/CompilerException.h"

Divide::Divide()
{
    m_args.push_back("...");
}

Token Divide::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    std::list<Token>& list = boost::get<std::list<Token>>(copy.at("...").value);
    auto it = list.begin();
    if((*it).type != TokenType::NUMBER)
    {
        throw InterpreterException("Není číslo", *it);
    }
    float division = boost::get<float>((*it).value);
    it++;
    while(it != list.end())
    {
        if((*it).type != TokenType::NUMBER)
        {
            throw InterpreterException("Není číslo", *it);
        }
        division = division / boost::get<float>((*it).value);
        it++;
    }
    return Token{
        TokenType::NUMBER,
        std::move(division),
        std::move(copy.at("...").filePos)
    };
}
