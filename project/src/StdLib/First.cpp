#include "../../include/StdLib/First.h"
#include "../../include/CompilerException.h"

First::First()
{
    m_args.push_back("kontejner");
}

Token First::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
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
        return list.front();
    }
    std::string string = boost::get<std::string>(collection.value);
    if(string.size() == 0)
    {
        throw InterpreterException("String je prázdný!", collection);
    }
    std::string result = string.substr(0, 1);
    return Token{
        TokenType::STRING,
        std::move(result),
        std::move(collection.filePos)
    };
}
