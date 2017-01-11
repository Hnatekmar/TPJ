#include "../../include/StdLib/Macro.h"
#include "../../include/CompilerException.h"
#include <list>

Macro::Macro(std::vector<std::shared_ptr<AST> > &code)
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

Context IMacro::argsToContext(std::vector<std::shared_ptr<AST>>& args, Context context)
{
    auto it = args.begin() + 1;
    for(std::string& argName : m_args)
    {
        if(argName == "...")
        {
            List<Token> variadic;
            while(it != args.end())
            {
                variadic = variadic.addBack(quote(*it));
                it++;
            }
            context[argName] = Token{
                TokenType::LIST,
                variadic,
                args.front()->value.filePos
            };
            break;
        }
        if(it == args.end())
        {
            throw InterpreterException("Neplatné množství argumentů", args.back()->value);
        }
        context[argName] = quote(*it);
        it++;
    }
    if(it != args.end())
    {
        throw InterpreterException("Neplatné množství argumentů", args.front()->value);
    }
    return context;
}

Token quote(std::shared_ptr<AST> &ast)
{
    if(ast->call)
    {
        return Token{
            TokenType::LIST,
            astToList(ast),
            ast->value.filePos
        };
    }
    Token copy = ast->value;
    copy.quote = true;
    return copy;
}

std::shared_ptr<AST> unquote(Token &value)
{
    if(value.type == TokenType::LIST)
    {
        return listToAst(boost::get<List<Token>>(value.value));
    }
    std::shared_ptr<AST> top(nullptr);
    Token copy = value;
    copy.quote = false;
    return std::make_shared<AST>(
                copy,
                top,
                false);
}

std::shared_ptr<AST> listToAst(const List<Token>& list)
{
    std::shared_ptr<AST> top(nullptr);
    std::shared_ptr<AST> node = std::make_shared<AST>(Token{}, top, true);
    if(list.size() == 0)
    {
        return node;
    }
    node->value = list.first();
    List<Token> it = list;
    while(!it.empty())
    {
        if(it.first().type == TokenType::LIST)
        {
            auto subNode = listToAst(boost::get<List<Token>>(it.first().value));
            subNode->call = true;
            node->children.push_back(subNode);
        }
        else
        {
            Token copy = it.first();
            copy.quote = false;
            node->children.push_back(std::make_shared<AST>(copy, node, false));
        }
        it = it.rest();
    }
    return node;
}

List<Token> astToList(std::shared_ptr<AST> &ast)
{
    List<Token> list;
    for(std::shared_ptr<AST>& elem : ast->children)
    {
        list = list.addBack(quote(elem));
    }
    return list;
}


std::shared_ptr<AST> IMacro::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
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
            return listToAst(boost::get<List<Token>>(token.value));
        }
        else
        {
            (*it)->evaluate(copy);
        }
    }
    assert(false);
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

