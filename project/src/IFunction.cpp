#include "../include/IFunction.h"
#include "../include/CompilerException.h"

Context IFunction::argsToContext(std::vector<std::shared_ptr<AST>>& args, Context& context)
{
    Context copy(context.begin(), context.end());
    auto it = args.begin() + 1;
    for(std::string& argName : m_args)
    {
        if(argName == "...")
        {
            std::list<Token> variadic;
            while(it != args.end())
            {
                variadic.push_back((*it)->evaluate(context));
                it++;
            }
            copy[argName] = Token{
                TokenType::LIST,
                std::move(variadic),
                args.front()->value.filePos
            };
            break;
        }
        if(it == args.end())
        {
            throw InterpreterException("Neplatné množství argumentů", args.back()->value);
        }
        copy[argName] = (*it)->evaluate(context);
        it++;
    }
    if(it != args.end())
    {
        throw InterpreterException("Neplatné množství argumentů", args.front()->value);
    }
    return std::move(copy);
}

unsigned int IFunction::s_id = 0;
IFunction::IFunction() : m_id(s_id++)
{
}

unsigned int IFunction::getId()
{
    return m_id;
}
