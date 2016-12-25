#include "../include/IFunction.h"
#include "../include/CompilerException.h"

Context IFunction::argsToContext(std::vector<std::shared_ptr<AST>>& args, Context& context)
{
    Context copy(context);
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
    return copy;
}

unsigned long IFunction::s_id = 0;
IFunction::IFunction() : m_id(s_id++),
                         m_args()
{
}

unsigned int IFunction::getId()
{
    return m_id;
}
