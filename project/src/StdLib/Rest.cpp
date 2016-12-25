#include "../../include/StdLib/Rest.h"
#include "../../include/CompilerException.h"

Rest::Rest()
{
    m_args.push_back("kontejner");
}

Token Rest::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    auto collection = copy.at("kontejner");
    if(collection.type != TokenType::STRING && collection.type != TokenType::LIST)
    {
        throw InterpreterException("Hodnota kontejner musí být list nebo string", collection);
    }
    if(collection.type == TokenType::LIST)
    {
        std::list<Token>& list = boost::get<std::list<Token>>(collection.value);
        if(list.size() == 0)
        {
            throw InterpreterException("List je prázdný!", collection);
        }
        auto it = list.begin();
        it++;
        std::list<Token> subList(it, list.end());
        return Token{
            TokenType::LIST,
            std::move(subList),
            std::move(copy.at("kontejner").filePos)
        };
    }
    std::string string = boost::get<std::string>(collection.value);
    if(string.size() == 0)
    {
        throw InterpreterException("String je prázdný!", collection);
    }
    return Token{
        TokenType::STRING,
        string.substr(1),
        collection.filePos
    };
}
