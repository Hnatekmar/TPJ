#ifndef GET_ARGUMENTS
#define GET_ARGUMENTS
#include "../IFunction.h"

class GetArguments : public IFunction
{
public:
    GetArguments();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
