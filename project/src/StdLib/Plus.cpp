#include "../../include/StdLib/Plus.h"
#include "../../include/CompilerException.h"

Plus::Plus()
{
    m_args.push_back("...");
}

Token Plus::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    List<Token> it = boost::get<List<Token>>(copy.at("...").value);
    if(it.first().type != TokenType::NUMBER)
    {
        throw InterpreterException("Není číslo", it.first());
    }
    float product = boost::get<float>(it.first().value);
    it = it.rest();
    while(!it.empty())
    {
        if(it.first().type != TokenType::NUMBER)
        {
            throw InterpreterException("Není číslo", it.first());
        }
        product = product + boost::get<float>(it.first().value);
        it = it.rest();
    }
    return Token{
        TokenType::NUMBER,
        std::move(product),
        std::move(copy.at("...").filePos)
    };
}
