#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "IFunction.h"

/**
 * @brief Reprezentuje uživatelem definovanou funkci
 */
class ASTFunction : public IFunction
{
    std::vector<std::shared_ptr<AST>> m_body;
    Context m_closure;
public:
    ASTFunction(std::vector<std::shared_ptr<AST>>& code, Context closure);
    Token execute(std::vector<std::shared_ptr<AST>> & args, Context & context) override;
};

#endif // ASTFUNCTION_H
