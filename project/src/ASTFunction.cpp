#include "../include/ASTFunction.h"
#include "../include/CompilerException.h"

ASTFunction::ASTFunction(std::vector<std::shared_ptr<AST>>& code, Context closure) : m_body(),
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
    Context copy = argsToContext(args, context);
    copy.insert(m_closure.begin(), m_closure.end());
    // Samotná evaluace funkce probíhá zde. Vrací se vždy hodnota posledního výrazu v těle funkce.
    for(auto it = m_body.begin(); it != m_body.end(); it++)
    {
        if(std::next(it) == m_body.end())
        {
            return (*it)->evaluate(copy);
        }
        else
        {
            std::cout << (*it)->evaluate(copy) << std::endl;
        }
    }
    
    return Token{}; // Nikdy se nezavolá je zde pouze pro uspokejení kompilátoru
}
