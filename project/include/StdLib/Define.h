#ifndef DEFINE_H
#define DEFINE_H

#include "../IFunction.h"
#include "../CompilerException.h"

class Define : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif // DEFINE_H
