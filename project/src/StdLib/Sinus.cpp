#include "../../include/StdLib/Sinus.h"
#include "../../include/CompilerException.h"
#include <cmath>

Sine::Sine()
{
    m_args = {"x"};
}

Token Sine::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& x = copy.at("x");
    if(x.type != TokenType::NUMBER)
    {
        throw InterpreterException("Argument x musí být číslo", x);
    }
    return Token{
        TokenType::NUMBER,
        static_cast<float>(sin(boost::get<float>(x.value))),
        {}
    };
}
