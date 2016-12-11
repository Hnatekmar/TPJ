#include "../include/Graphics.h"
#include "../include/CompilerException.h"

Graphics::Graphics() : m_args{"seznamVykreslitelnychObjektu"}
{
}

Token Graphics::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Token list = argsToContext(args, context).at("seznamVykreslitelnychObjektu");
    if(list.type != TokenType::LIST)
    {
        throw InterpreterException("Argument musí být typu list", list);
    }
    std::list<Token> objects = boost::get<std::list<Token>>(list.value);
    std::cout << "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">";
    for(Token& obj : objects)
    {
    }
    std::cout << "</svg>";
}
