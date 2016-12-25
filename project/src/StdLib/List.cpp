#include "../../include/StdLib/List.h"

ListFn::ListFn()
{
    m_args.push_back("...");
}

Token ListFn::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    return std::move(copy.at("..."));
}
