#ifndef SQRT
#define SQRT

#include "../IFunction.h"

class Sqrt : public IFunction
{
public:
    Sqrt();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
