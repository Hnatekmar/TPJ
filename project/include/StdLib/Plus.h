#ifndef PLUS
#define PLUS

#include "../IFunction.h"

class Plus : public IFunction
{
public:
    Plus();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};


#endif
