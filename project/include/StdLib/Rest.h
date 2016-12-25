#ifndef REST
#define REST

#include "../IFunction.h"

class Rest : public IFunction
{
public:
    Rest();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
