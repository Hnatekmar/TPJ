#ifndef GRAPHICS_OBJECT
#define GRAPHICS_OBJECT

#include <map>
#include <list>
#include <string>

class GraphicsObject
{
    std::map<std::string, std::string> m_params;
    std::list<GraphicsObject> m_children;
    std::string m_name;
public:
    GraphicsObject(std::string name, std::map<std::string, std::string> params, std::list<GraphicsObject> children);
    std::string toString();
};

#endif
