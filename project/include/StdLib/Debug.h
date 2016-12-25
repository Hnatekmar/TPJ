#ifndef DEBUG
#define DEBUG

#include "../IFunction.h"

class Debug : public IFunction
{
public:
    Debug();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
