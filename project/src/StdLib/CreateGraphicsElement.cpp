#include "../../include/StdLib/CreateGraphicsElement.h"
#include "../../include/CompilerException.h"

CreateGraphicsElement::CreateGraphicsElement()
{
   m_args.push_back("jmenoElementu");
   m_args.push_back("argumenty");
   m_args.push_back("naslednici");
}

Token CreateGraphicsElement::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    Token& elementName = copy.at("jmenoElementu");
    if(elementName.type != TokenType::STRING)
    {
        throw InterpreterException("Položka není typu string!", elementName);
    }
    std::string name = boost::get<std::string>(elementName.value);
    Token& arguments = copy.at("argumenty");
    if(arguments.type != TokenType::LIST)
    {
        throw InterpreterException("Položka není typu list!", arguments);
    }
    std::map<std::string, std::string> argMap;
    List<Token>& argList = boost::get<List<Token>>(arguments.value);
    if(argList.size() % 2 != 0)
    {
        throw InterpreterException("Argumenty musí být ve formátu (list nazevArgumentu hodnotaArgumentu ...)", arguments);
    }
    auto it = argList;
    while(!it.empty())
    {
        if(it.first().type != TokenType::STRING)
        {
            throw InterpreterException("Položka není typu string!", it.first());
        }
        std::string key = boost::get<std::string>(it.first().value);
        it = it.rest();
        if(it.first().type != TokenType::STRING)
        {
            throw InterpreterException("Položka není typu string!", it.first());
        }
        std::string value = boost::get<std::string>(it.first().value);
        argMap[key] = value;
        it = it.rest();
    }

    Token& children = copy.at("naslednici");

    if(children.type != TokenType::LIST)
    {
        throw InterpreterException("Položka není typu list!", arguments);
    }
    List<Token> childrenList = boost::get<List<Token>>(children.value);
    return Token{
        TokenType::GRAPHICS_ELEMENT,
        std::make_shared<GraphicsObject>(name, argMap, childrenList),
        elementName.filePos
    };
}
