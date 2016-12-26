#ifndef TO_STRING
#define TO_STRING

#include "../IFunction.h"
class ToString : public IFunction
{
public:
    ToString();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
