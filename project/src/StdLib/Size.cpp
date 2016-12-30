#include "../../include/StdLib/Size.h"
#include "../../include/CompilerException.h"

Size::Size()
{
    m_args.push_back("kotejner");
}

Token Size::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    auto collection = copy.at("kotejner");
    if(collection.type != TokenType::STRING && collection.type != TokenType::LIST)
    {
        throw InterpreterException("Hodnota kontejner musí být list nebo string", collection);
    }
    if(collection.type == TokenType::LIST)
    {
        List<Token> list = boost::get<List<Token>>(collection.value);
        return Token{
            TokenType::NUMBER,
            static_cast<float>(list.size()),
            collection.filePos
        };
    }
    std::string string = boost::get<std::string>(collection.value);
    return Token{
        TokenType::NUMBER,
        static_cast<float>(string.size()),
        collection.filePos
    };
}
