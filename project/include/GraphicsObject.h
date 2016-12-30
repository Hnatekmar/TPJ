#ifndef GRAPHICS_OBJECT
#define GRAPHICS_OBJECT

#include <map>
#include "List.h"
#include <string>
struct Token;
class GraphicsObject
{
    std::map<std::string, std::string> m_params;
    List<Token> m_children;
    std::string m_name;
public:
    GraphicsObject(std::string name, std::map<std::string, std::string> params, List<Token> children);
    std::string toString();
};

#endif
