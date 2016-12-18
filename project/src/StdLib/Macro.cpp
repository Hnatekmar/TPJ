#include "../../include/StdLib/Macro.h"
#include "../../include/CompilerException.h"

Macro::Macro(std::vector<std::shared_ptr<AST> > &code) : 	m_body(),
                                                            m_args()
{
    if(code.size() < 3)
    {
        throw InterpreterException("Makro potřebuje minimálně neprázdný seznam argumentů a tělo, které obsahuje minimálně jeden výraz!", code.at(0)->value);
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

Context Macro::argsToContext(std::vector<std::shared_ptr<AST>>& args, Context context)
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
                variadic.push_back(Token{
                                       TokenType::LIST,
                                       astToList((*it)->children),
                                       (*it)->value.filePos
                           });
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
        copy[argName] = Token{
                TokenType::LIST,
                astToList((*it)->children),
                (*it)->value.filePos
            };
        it++;
    }
    if(it != args.end())
    {
        throw InterpreterException("Neplatné množství argumentů", args.front()->value);
    }
    return std::move(copy);
}

std::shared_ptr<AST> listToAst(std::list<Token> &list)
{
    std::shared_ptr<AST> top(nullptr);
    std::shared_ptr<AST> node = std::make_shared<AST>(Token{}, top, true);
    node->value = list.front();
    for(Token& elem : list)
    {
        if(elem.type == TokenType::LIST)
        {
            auto subNode = listToAst(boost::get<std::list<Token>>(elem.value));
            subNode->call = true;
            node->children.push_back(subNode);
        }
        else
        {
            node->children.push_back(std::make_shared<AST>(elem, node, false));
        }
    }
    return node;
}

std::list<Token> astToList(std::vector<std::shared_ptr<AST> > &ast)
{
    std::list<Token> list;
    for(std::shared_ptr<AST>& elem : ast)
    {
        if(elem->call)
        {
            list.push_back(Token{
                               TokenType::LIST,
                               astToList(elem->children),
                               elem->value.filePos
                           });
        }
        else
        {
            list.push_back(elem->value);
        }
    }
    return list;
}


std::shared_ptr<AST> Macro::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    // Samotná evaluace funkce probíhá zde. Vrací se vždy hodnota posledního výrazu v těle funkce.
    for(auto it = m_body.begin(); it != m_body.end(); it++)
    {
        if(std::next(it) == m_body.end())
        {
            Token token = (*it)->evaluate(copy);
            if(token.type != TokenType::LIST)
            {
                throw InterpreterException("Makro musí vracet list", token);
            }
            return listToAst(boost::get<std::list<Token>>(token.value));
        }
        else
        {
            (*it)->evaluate(copy);
        }
    }
    return nullptr;
}


Token CreateMacro::execute(std::vector<std::shared_ptr<AST> > &args, Context &)
{
   Token returnVal{
        TokenType::MACRO_FN,
        std::make_shared<Macro>(args),
        {}
    };
   return returnVal;
}
