#include "../../include/StdLib/CreateFunction.h"
#include "../../include/CompilerException.h"
#include "../../include/ASTFunction.h"

#include <memory>

Token CreateFunction::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    if(args.size() < 3)
    {
        throw InterpreterException("Funkce potřebuje minimálně neprázdný seznam argumentů a tělo, které obsahuje minimálně jeden výraz!", args.at(0)->value);
    }
    return Token{
        TokenType::FUNCTION,
        std::make_shared<ASTFunction>(args, context),
        args.at(0)->value.filePos
    };
}
