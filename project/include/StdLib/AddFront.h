#ifndef ADDFRONT
#define ADDFRONT

#include "../IFunction.h"

class AddFront : public IFunction
{
public:
    AddFront();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
