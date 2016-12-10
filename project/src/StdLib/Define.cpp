#include "../../include/StdLib/Define.h"


Token Define::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
        if(args.size() != 3)
        {
            throw InterpreterException("Funkce definuj přebírá 2 argumenty.", args.front()->value);
        }
        auto what = args.at(1)->value; // Identifikátor, který nahradí hodnotu
        if(what.type != TokenType::IDENTIFIER)
        {
            throw InterpreterException("Definuj potřebuje validní identifikátor", args.front()->evaluate(context));

        }
        context[boost::get<std::string>(what.value)] = args.at(2)->evaluate(context);
        return context[boost::get<std::string>(what.value)];
}
