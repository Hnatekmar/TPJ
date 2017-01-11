#include "../include/GraphicsObject.h"
#include <sstream>
#include "../include/Token.h"

GraphicsObject::GraphicsObject(std::string name, std::map<std::string, std::string> params, List<Token> children):
    m_params(params),
    m_children(children),
    m_name(name)
{
}

std::string GraphicsObject::toString()
{
    std::stringstream ss;
    ss << "<" << m_name << " ";
    for(auto& pair : m_params)
    {
        ss << pair.first << "=\"" << pair.second << "\" ";
    }
    ss << ">";
    auto it = m_children;
    while(!it.empty())
    {
        if(it.first().type == TokenType::GRAPHICS_ELEMENT)
        {
            auto graphics = boost::get<std::shared_ptr<GraphicsObject>>(it.first().value);
            ss << graphics->toString();
        }
        else
        {
            ss << it.first();
        }
        it = it.rest();
    }
    ss << "</" << m_name << ">";
    return ss.str();
}
