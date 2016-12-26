#include "../../include/StdLib/ToString.h"
#include <sstream>

ToString::ToString()
{
    m_args.push_back("hodnota");
}

Token ToString::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    std::stringstream ss;
    ss << copy.at("hodnota");
    return Token{
        TokenType::STRING,
        ss.str(),
        copy.at("hodnota").filePos
    };
}
