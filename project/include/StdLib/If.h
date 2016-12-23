#ifndef IF
#define IF

#include "Macro.h"

class If : public IMacro
{
public:
    If();
    std::shared_ptr<AST> expand(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
