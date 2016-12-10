#ifndef FUNCTION_H
#define FUNCTION_H

#include "Token.h"
#include <memory>
#include <vector>
#include "AST.h"

/**
 * @brief Interface popisující funkci.
 */
class IFunction
{
protected:
    std::vector<std::string> m_args;
    Context argsToContext(std::vector<std::shared_ptr<AST>>& args, Context& context);
    
public:
    /**
     * @brief Provede funkci na základě kontextu a argumentů
     */
    virtual Token execute(std::vector<std::shared_ptr<AST>>& args, Context& context) = 0;
};

#endif // FUNCTION_H
