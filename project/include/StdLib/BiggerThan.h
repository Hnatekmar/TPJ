#ifndef BIGGERTHAN
#define BIGGERTHAN

#include "../IFunction.h"

class BiggerThan : public IFunction
{
public:
    BiggerThan();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
