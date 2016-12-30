#include "../../include/StdLib/Rest.h"
#include "../../include/CompilerException.h"

Rest::Rest()
{
    m_args.push_back("kontejner");
}

Token Rest::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    auto collection = copy.at("kontejner");
    if(collection.type != TokenType::STRING && collection.type != TokenType::LIST)
    {
        throw InterpreterException("Hodnota kontejner musí být list nebo string", collection);
    }
    if(collection.type == TokenType::LIST)
    {
        List<Token> list = boost::get<List<Token>>(collection.value);
        return Token{
            TokenType::LIST,
            list.rest(),
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
