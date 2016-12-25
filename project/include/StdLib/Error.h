#ifndef ERROR
#define ERROR

#include "../IFunction.h"

class Error : public IFunction
{
public:
    Error();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
