#ifndef IF
#define IF

#include "../IFunction.h"

class If : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
