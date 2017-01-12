#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>
#include <vector>
#include "AST.h"
#include "List.h"

/**
 * @brief Interface popisující funkci.
 */
class IFunction
{
protected:
    static unsigned long s_id;
    unsigned long m_id;
    std::vector<std::string> m_args;
    void argsToContext(std::vector<std::shared_ptr<AST>>& args, Context& context);

public:
    IFunction();
    unsigned int getId();
    List<Token> argList();

    /**
     * @brief Provede funkci na základě kontextu a argumentů
     */
    virtual Token execute(std::vector<std::shared_ptr<AST>>& args, Context& context) = 0;
    virtual ~IFunction() = default;
};


#endif // FUNCTION_H
