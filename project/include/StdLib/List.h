#ifndef LIST_CREATE_H
#define LIST_CREATE_H

#include "../IFunction.h"

class ListFn : public IFunction
{
public:
    ListFn();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
