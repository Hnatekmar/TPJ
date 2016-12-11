#ifndef EQUALS
#define EQUALS

#include "../IFunction.h"

class Equals : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
