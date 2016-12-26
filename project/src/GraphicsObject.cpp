#include "../include/GraphicsObject.h"
#include <sstream>

GraphicsObject::GraphicsObject(std::string name, std::map<std::string, std::string> params, std::list<GraphicsObject> children):
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
        ss << pair.first << " = \"" << pair.second << "\" ";
    }
    ss << ">";
    for(auto& child : m_children)
    {
        ss << child.toString();
    }
    ss << "</" << m_name << ">";
    return ss.str();
}
