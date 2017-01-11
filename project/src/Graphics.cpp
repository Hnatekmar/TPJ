#include "../include/Graphics.h"
#include "../include/CompilerException.h"

Graphics::Graphics()
{
    m_args = {"seznamVykreslitelnychObjektu",
              "vyska",
              "sirka"};
}

Token Graphics::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    argsToContext(args, context);
    Token list = context.at("seznamVykreslitelnychObjektu");
    Token width = context.at("vyska");
    Token height = context.at("sirka");
    if(list.type != TokenType::LIST)
    {
        throw InterpreterException("Argument musí být typu list", list);
    }

    if(width.type != TokenType::NUMBER)
    {
        throw InterpreterException("Argument musí být typu číslo", width);
    }

    if(height.type != TokenType::NUMBER)
    {
        throw InterpreterException("Argument musí být typu číslo", height);
    }

    List<Token> objects = boost::get<List<Token>>(list.value);
    std::cout << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">";
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
