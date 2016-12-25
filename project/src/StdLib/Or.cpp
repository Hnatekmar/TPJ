#include "../../include/StdLib/Or.h"
#include "../../include/CompilerException.h"

Or::Or()
{
    m_args.push_back("...");
}

std::shared_ptr<AST> Or::expand(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
   Context copy = argsToContext(args, context);
   std::list<Token>& list = boost::get<std::list<Token>>(copy.at("...").value);
   bool result = false;
   for(Token& token : list)
   {
       Token tokenVal = unquote(token)->evaluate(context);
       if(tokenVal.type != TokenType::BOOL)
       {
           throw InterpreterException("Hodnota není logická", tokenVal);
       }
       result = result || boost::get<bool>(tokenVal.value);
       if(!result)
       {
           break;
       }
   }
   std::shared_ptr<AST> parent(nullptr);
   return std::make_shared<AST>(Token{
       TokenType::BOOL,
       result,
       copy.at("...").filePos
   }, parent, false);
}
