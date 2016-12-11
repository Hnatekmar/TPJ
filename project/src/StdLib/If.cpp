#include "../../include/StdLib/If.h"
#include "../../include/CompilerException.h"

Token If::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    if(args.size() != 4)
    {
        throw InterpreterException("pokud bere 3 argumenty", args.at(0)->value);
    }
    auto assertion = args.at(1)->evaluate(context);
    if(assertion.type != TokenType::BOOL)
    {
        throw InterpreterException("První argument musí být logická hodnota", assertion);
    }
    if(boost::get<bool>(assertion.value))
    {
        return args.at(2)->evaluate(context);
    }
    else
    {
        return args.at(3)->evaluate(context);
    }
}
