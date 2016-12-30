#include "../../include/StdLib/AddFront.h"
#include "../../include/CompilerException.h"

AddFront::AddFront()
{
    m_args.push_back("kolekce");
    m_args.push_back("hodnota");
}

Token AddFront::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& list = copy.at("kolekce");
    Token value = copy.at("hodnota");
    if(list.type != TokenType::LIST && list.type != TokenType::STRING)
    {
        throw InterpreterException("Hodnota musí být typu list", list);
    }
    if(list.type == TokenType::LIST)
    {
        List<Token> collection = boost::get<List<Token>>(list.value);
        collection = collection.add(value);
        return Token{
        TokenType::LIST,
            collection,
            std::move(list.filePos)
        };
    }
    if(value.type != TokenType::STRING)
    {
        throw InterpreterException("Pokud spojuji string hodnota musí být také string", value);
    }
    std::string newString = boost::get<std::string>(value.value) + boost::get<std::string>(list.value);
    return Token{
        TokenType::STRING,
        std::move(newString),
        args.front()->value.filePos
    };
}
