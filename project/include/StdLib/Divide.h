#ifndef DIVIDE
#define DIVIDE

#include "../IFunction.h"

class Divide : public IFunction
{
public:
    Divide();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
