#ifndef CREATE_FUNCTION_H
#define CREATE_FUNCTION_H

#include "../IFunction.h"

class CreateFunction : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif // CREATE_FUNCTION_H
