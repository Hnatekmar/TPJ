#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "IFunction.h"

class Graphics : public IFunction
{
public:
    Graphics();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif // GRAPHICS_H
