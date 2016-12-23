#ifndef QUOTE
#define QUOTE

#include "../IFunction.h"
#include "Macro.h"

class Quote : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &) override;
};

#endif
