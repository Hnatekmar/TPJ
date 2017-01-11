#include "../../include/StdLib/Cosinus.h"
#include "../../include/CompilerException.h"
#include <cmath>

Cosine::Cosine()
{
    m_args = {"x"};
}

Token Cosine::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
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
        static_cast<float>(cos(boost::get<float>(x.value))),
        {}
    };
}
