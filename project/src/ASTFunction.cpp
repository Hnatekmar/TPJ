#include "../include/ASTFunction.h"
#include "../include/CompilerException.h"
#include "../include/StdLib/Macro.h"

ASTFunction::ASTFunction(std::vector<std::shared_ptr<AST>>& code, Context closure) :
                                                                                     IFunction(),
                                                                                     m_body(),
                                                                                     m_closure(closure)
{
    if(code.size() < 3)
    {
        throw InterpreterException("Funkce potřebuje minimálně neprázdný seznam argumentů a tělo, které obsahuje minimálně jeden výraz!", code.at(0)->value);
    }
    for(auto it = code.at(1)->children.begin(); it != code.at(1)->children.end(); it++)
    {
        std::shared_ptr<AST>& arg = (*it);
        if(arg->value.type != TokenType::IDENTIFIER)
        {
            throw InterpreterException("Argument musí být validní identifikátor", arg->value);
        }
        std::string argName = boost::get<std::string>(arg->value.value);
        if(argName == "..." && std::next(it) != code.at(1)->children.end())
        {
            throw InterpreterException("Variadická funkce musí mít označení pro variabilní počet argumentů na konci listu argumentů.", arg->value);
        }
        m_args.push_back(argName);
    }
    m_body.insert(m_body.begin(), code.begin() + 2, code.end());
}

Token ASTFunction::execute(std::vector<std::shared_ptr<AST>>& args, Context& context)
{
    // Nejprve je potřeba vytvořit nový context do kterého se vloží i argumenty funkce
    Context copy(context);
    argsToContext(args, copy);
    copy.insert(m_closure.begin(), m_closure.end());
    do
    {
        // Samotná evaluace funkce probíhá zde. Vrací se vždy hodnota posledního výrazu v těle funkce.
        for(auto it = m_body.begin(); it != m_body.end(); it++)
        {
            std::shared_ptr<AST> evaluate = *it;
            while(evaluate->call)
            {
                auto fn = evaluateIdentifier(evaluate->children.front()->value, copy);
                if(fn.type == TokenType::MACRO_FN)
                {
                    evaluate = boost::get<std::shared_ptr<IMacro>>(fn.value)->expand(evaluate->children, copy);
                }
                else
                {
                    break;
                }
            }
            if(std::next(it) == m_body.end())
            {
                if(evaluate->call)
                {
                    auto fn1 = evaluateIdentifier(evaluate->children.front()->value, copy);
                    auto fn2 = evaluateIdentifier(args.front()->value, copy);
                    if(getKind(fn1.value) == getKind(fn2.value) && getKind(fn1.value) == MirageKind::function)
                    {
                        auto fn1Ptr = boost::get<std::shared_ptr<IFunction>>(fn1.value);
                        auto fn2Ptr = boost::get<std::shared_ptr<IFunction>>(fn2.value);
                        if(fn1Ptr->getId() == fn2Ptr->getId())
                        {
                            argsToContext(evaluate->children, copy);
                            it = m_body.begin();
                            continue;
                        }
                    }
                }
                return evaluate->evaluate(copy);
            }
            else
            {
                evaluate->evaluate(copy);
            }
        }
    } while(true);
    return Token{}; // Nikdy se nezavolá je zde pouze pro uspokejení kompilátoru
}
