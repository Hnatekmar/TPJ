#ifndef SINUS
#define SINUS

#include "../IFunction.h"

class Sine : public IFunction
{
public:
    Sine();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
