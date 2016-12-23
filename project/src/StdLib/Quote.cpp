#include "../../include/StdLib/Quote.h"

Token Quote::execute(std::vector<std::shared_ptr<AST> > &args, Context &)
{
    return quote(args.at(1));
}
