#ifndef FIRST
#define FIRST

#include "../IFunction.h"

class First : public IFunction
{
public:
    First();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
