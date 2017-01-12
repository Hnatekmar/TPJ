#include "../../include/StdLib/GetArguments.h"

GetArguments::GetArguments()
{
    m_args = {"fn"};
}

Token GetArguments::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    std::shared_ptr<IFunction>& fn = boost::get<std::shared_ptr<IFunction>>(copy.at("fn").value);
    return Token{
                        TokenType::LIST,
                        fn->argList(),
        {}};
}
