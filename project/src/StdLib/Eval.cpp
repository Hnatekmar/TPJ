#include "../../include/StdLib/Eval.h"

Token Eval::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    std::shared_ptr<AST>& doEvaluate = args.at(1);
    if(doEvaluate->value.type == TokenType::LIST)
    {
        return listToAst(boost::get<std::list<Token>>(doEvaluate->value.value))->evaluate(context);
    }
    return doEvaluate->evaluate(context);
}
