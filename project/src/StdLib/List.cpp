#include "../../include/StdLib/List.h"

ListFn::ListFn()
{
    m_args.push_back("...");
}

Token ListFn::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    return copy.at("...");
}
