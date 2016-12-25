#ifndef TIMES
#define TIMES

#include "../IFunction.h"

class Times : public IFunction
{
public:
    Times();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
