#ifndef ADD_BACK
#define ADD_BACK

#include "../IFunction.h"

class AddBack : public IFunction
{
public:
    AddBack();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
