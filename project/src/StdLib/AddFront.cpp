#include "../../include/StdLib/AddFront.h"
#include "../../include/CompilerException.h"

AddFront::AddFront()
{
    m_args.push_back("kolekce");
    m_args.push_back("hodnota");
}

Token AddFront::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    Token& list = copy.at("kolekce");
    Token value = copy.at("hodnota");
    if(list.type != TokenType::LIST)
    {
        throw InterpreterException("Hodnota musí být typu list", list);
    }
    std::list<Token> collection = boost::get<std::list<Token>>(list.value);
    collection.push_front(value);
    return Token{
        TokenType::LIST,
        std::move(collection),
        std::move(list.filePos)
    };
}
