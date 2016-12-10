#ifndef NOT_H
#define NOT_H

#include "../IFunction.h"

class Not : public IFunction
{
public:
    Not();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif // NOT_H
