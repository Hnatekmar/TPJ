#ifndef IMPORT_H
#define IMPORT_H

#include "../IFunction.h"
#include "../Parser.h"

class Import : public IFunction
{
    Parser& m_parser;
public:
    Import(Parser& parser);
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif // IMPORT_H
