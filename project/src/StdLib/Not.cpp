#include "../../include/StdLib/Not.h"

Not::Not()
{
    m_args = {
        "x"
    };
}

Token Not::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    return Token{
        TokenType::BOOL,
        static_cast<bool>(!boost::get<bool>(copy.at("x").value)),
        args.at(0)->value.filePos
    };
}
