#ifndef OR
#define OR

#include "../../include/StdLib/Macro.h"

class Or : public IMacro
{
public:
    Or();
    std::shared_ptr<AST> expand(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
