#include "../../include/StdLib/If.h"
#include "../../include/CompilerException.h"

If::If()
{
   m_args.push_back("predikat");
   m_args.push_back("hodnota1");
   m_args.push_back("hodnota2");
}

std::shared_ptr<AST> If::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    auto predicate = unquote(copy.at("predikat"))->evaluate(context);
    if(predicate.type != TokenType::BOOL)
    {
        throw InterpreterException("predikat musí být převeditelný na logickou hodnotu", predicate);
    }
    if(boost::get<bool>(predicate.value))
    {
        return unquote(copy.at("hodnota1"));
    }
    else
    {
        return unquote(copy.at("hodnota2"));
    }
}
