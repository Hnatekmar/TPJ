#include "../../include/StdLib/Eval.h"

Token Eval::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Token doEvaluate = args.at(1)->evaluate(context);
    return unquote(doEvaluate)->evaluate(context);
}
