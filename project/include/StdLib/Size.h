#ifndef SIZE
#define SIZE

#include "../IFunction.h"

class Size : public IFunction
{
public:
    Size();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
