#ifndef AND
#define AND

#include "../IFunction.h"

class And : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
