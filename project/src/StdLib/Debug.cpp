#include "../../include/StdLib/Debug.h"
#include <iostream>

Debug::Debug()
{
    m_args.push_back("hodnota");
}

Token Debug::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
    Context copy = argsToContext(args, context);
    std::cout << "Hodnota: " << copy.at("hodnota") << std::endl;
    char yesOrNo = 'f';
    while(yesOrNo != 'A')
    {
        std::cout << "Přejete si pokračovat? (A / N)" << std::endl;
        std::cin >> std::noskipws >> yesOrNo;
        if(yesOrNo == 'N')
        {
            std::cout << "Končím debugování." << std::endl;
            std::exit(0);
        }
    }
    return copy.at("hodnota");
}
