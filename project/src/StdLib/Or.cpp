#include "../../include/StdLib/Or.h"
#include "../../include/CompilerException.h"

Or::Or()
{
    m_args.push_back("...");
}

std::shared_ptr<AST> Or::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, copy);
    List<Token> list = boost::get<List<Token>>(copy.at("...").value);
    bool result = false;
    while(!list.empty())
    {
        auto token = list.first();
        Token tokenVal = unquote(token)->evaluate(context);
        if(tokenVal.type != TokenType::BOOL)
        {
            throw InterpreterException("Hodnota není logická", tokenVal);
        }
        result = result || boost::get<bool>(tokenVal.value);
        if(!result)
        {
            break;
        }
        list = list.rest();
    }
    std::shared_ptr<AST> parent(nullptr);
    return std::make_shared<AST>(Token{
                                         TokenType::BOOL,
                                         result,
                                         copy.at("...").filePos
                                 }, parent, false);
}
