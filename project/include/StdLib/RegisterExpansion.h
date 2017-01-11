#ifndef REGISTER_EXPANSION
#define REGISTER_EXPANSION

#include "Macro.h"

class RegisterExpansion : public IMacro
{
public:
    RegisterExpansion();
    std::shared_ptr<AST> expand(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
