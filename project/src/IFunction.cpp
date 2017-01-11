#include "../include/IFunction.h"
#include "../include/CompilerException.h"
#include <sstream>


void IFunction::argsToContext(std::vector<std::shared_ptr<AST>>& args, Context& context)
{
    Context copy(context);
    auto it = args.rbegin();
    List<Token> evaluatedArgs;
    for(auto argIt = m_args.rbegin(); argIt != m_args.rend(); argIt++)
    {
        const std::string& argName = (*argIt);
        if(argName == "...")
        {
            List<Token> variadic;
            size_t count = args.size() - m_args.size();
            while(count > 0)
            {
                variadic = variadic.add((*it)->evaluate(copy));
                it++;
                count--;
            }
            context[argName] = Token{
                TokenType::LIST,
                variadic,
                args.front()->value.filePos
            };
            evaluatedArgs = evaluatedArgs.add(context[argName]);
            continue;
        }
        if(it == args.rend())
        {
            std::stringstream ss;
            ss << "Neplatné množství argumentů očekával jsem (";
            for(std::string& arg : m_args)
            {
                ss << arg << " ";
            }
            ss << ")";
            ss << " dostal jsem " << args.size() << " argumentů";
            throw InterpreterException(ss.str(), args.front()->evaluate(context));
        }
        context[argName] = (*it)->evaluate(copy);
        evaluatedArgs = evaluatedArgs.add(context[argName]);
        it++;
    }
    if(it != args.rend() - 1)
    {
        std::stringstream ss;
        ss << "Neplatné množství argumentů očekával jsem (";
        for(std::string& arg : m_args)
        {
            ss << arg << " ";
        }
        ss << ") a dostal jsem " << args.size() - 1 << " argumentů" << std::endl;
        size_t argNum = 0;
        evaluatedArgs = evaluatedArgs.rest();
        while(!evaluatedArgs.empty())
        {
            ss << '\t' << "Argument číslo " << argNum << ' ' << evaluatedArgs.first() << std::endl;
            argNum++;
            evaluatedArgs = evaluatedArgs.rest();
        }
        throw InterpreterException(std::move(ss.str()), args.front()->evaluate(context));
    }
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
