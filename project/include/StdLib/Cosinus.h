#ifndef COSINUS
#define COSINUS

#include "../IFunction.h"

class Cosine : public IFunction
{
public:
    Cosine();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
