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
    Context copy = argsToContext(args, context);
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
    std::list<Token>& argList = boost::get<std::list<Token>>(arguments.value);
    if(argList.size() % 2 != 0)
    {
        throw InterpreterException("Argumenty musí být ve formátu (list nazevArgumentu hodnotaArgumentu ...)", arguments);
    }
    auto it = argList.begin();
    while(it != argList.end())
    {
        if((*it).type != TokenType::STRING)
        {
            throw InterpreterException("Položka není typu string!", (*it));
        }
        std::string key = boost::get<std::string>((*it).value);
        it++;
        if((*it).type != TokenType::STRING)
        {
            throw InterpreterException("Položka není typu string!", (*it));
        }
        std::string value = boost::get<std::string>((*it).value);
        argMap[key] = value;
        it++;
    }

    Token& children = copy.at("naslednici");

    if(children.type != TokenType::LIST)
    {
        throw InterpreterException("Položka není typu list!", arguments);
    }
    std::list<Token> childrenList = boost::get<std::list<Token>>(children.value);
    std::list<GraphicsObject> objectList;
    auto childIt = childrenList.begin();
    while(childIt != childrenList.end())
    {
        if((*childIt).type != TokenType::GRAPHICS_ELEMENT)
        {
            throw InterpreterException("Položka není typu element!", (*childIt));
        }
        objectList.push_back(*boost::get<std::shared_ptr<GraphicsObject>>((*childIt).value).get());
        childIt++;
    }

    return Token{
        TokenType::GRAPHICS_ELEMENT,
        std::make_shared<GraphicsObject>(name, argMap, objectList),
        elementName.filePos
    };
}
