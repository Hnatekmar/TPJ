#include "../../include/StdLib/Error.h"
#include "../../include/CompilerException.h"

Error::Error()
{
        m_args.push_back("hodnota");
}

Token Error::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy(context);
    argsToContext(args, copy);
    throw InterpreterException("Kritická chyba vyvolaná z aplikace", copy.at("hodnota"));
}
