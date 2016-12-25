#ifndef MINUS
#define MINUS

#include "../IFunction.h"

class Minus : public IFunction
{
public:
    Minus();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
