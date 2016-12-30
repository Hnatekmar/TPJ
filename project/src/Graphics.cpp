#include "../include/Graphics.h"
#include "../include/CompilerException.h"

Graphics::Graphics()
{
    m_args = {"seznamVykreslitelnychObjektu"};
}

Token Graphics::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    argsToContext(args, context);
    Token list = context.at("seznamVykreslitelnychObjektu");
    if(list.type != TokenType::LIST)
    {
        throw InterpreterException("Argument musí být typu list", list);
    }
    List<Token> objects = boost::get<List<Token>>(list.value);
    std::cout << "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">";
    while(!objects.empty())
    {
        if(objects.first().type != TokenType::GRAPHICS_ELEMENT)
        {
            std::cout << objects.first();
        }
        else
        {
            std::cout << boost::get<std::shared_ptr<GraphicsObject>>(objects.first().value)->toString();
        }
        objects = objects.rest();
    }
    std::cout << "</svg>";
    std::exit(0);
    return Token{};
}
