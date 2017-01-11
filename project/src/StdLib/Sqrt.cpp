#include "../../include/StdLib/Sqrt.h"
#include "../../include/CompilerException.h"
#include <cmath>

Sqrt::Sqrt()
{
    m_args = {"x"};
}

Token Sqrt::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& x = copy.at("x");
    if(x.type != TokenType::NUMBER)
    {
        throw InterpreterException("Hodnota musí být číslo", x);
    }
    return Token{
        TokenType::NUMBER,
        static_cast<float>(sqrt(boost::get<float>(x.value))),
        {}
    };
}
