#ifndef EVAL
#define EVAL

#include "../IFunction.h"
#include "Macro.h"

class Eval : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
