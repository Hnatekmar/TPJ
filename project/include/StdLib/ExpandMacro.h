#ifndef EXPANDMACRO
#define EXPANDMACRO

#include "Macro.h"

class ExpandMacro : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
