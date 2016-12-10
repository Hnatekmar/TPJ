#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "IFunction.h"

class ASTFunction :  IFunction
{
    std::vector<std::shared_ptr<AST>> m_body;
public:
    ASTFunction(std::vector<std::shared_ptr<AST>>& code);
    virtual Token execute(std::vector<std::shared_ptr<AST>> & args, Context & context) override;
};

#endif // ASTFUNCTION_H
