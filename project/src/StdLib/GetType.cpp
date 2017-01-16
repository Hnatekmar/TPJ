#include "../../include/StdLib/GetType.h"

GetType::GetType()
{
    m_args.push_back("hodnota");
}

Token GetType::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& value = copy.at("hodnota");
    return Token{
        TokenType::STRING,
        m_tokenTypeToString.at(value.type),
        value.filePos
    };
}
