#include "../../include/StdLib/Times.h"
#include "../../include/CompilerException.h"

Times::Times()
{
    m_args.push_back("...");
}

Token Times::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    List<Token> it = boost::get<List<Token>>(copy.at("...").value);
    float product = 1;
    while(!it.empty())
    {
        if(it.first().type != TokenType::NUMBER)
        {
            throw InterpreterException("Není číslo", it.first());
        }
        product = product * boost::get<float>(it.first().value);
        it = it.rest();
    }
    return Token{
        TokenType::NUMBER,
        std::move(product),
        std::move(copy.at("...").filePos)
    };
}
