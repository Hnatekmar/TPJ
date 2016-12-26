#ifndef CREATE_GRAPHICS_ELEMENT
#define CREATE_GRAPHICS_ELEMENT

#include "../IFunction.h"

class CreateGraphicsElement : public IFunction
{
public:
    CreateGraphicsElement();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
