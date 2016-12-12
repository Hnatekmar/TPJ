#include "../../include/StdLib/Quote.h"

Token Quote::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    std::shared_ptr<AST>& doNotEvaluate = args.at(1);
    if(doNotEvaluate->call)
    {
        return Token{
                TokenType::LIST,
                astToList(doNotEvaluate->children),
                doNotEvaluate->value.filePos
        };
    }
    return doNotEvaluate->evaluate(context);
}
