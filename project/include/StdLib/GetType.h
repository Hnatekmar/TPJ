#ifndef GET_TYPE
#define GET_TYPE
#include "../IFunction.h"
#include <map>

class GetType : public IFunction
{
    std::map<TokenType, std::string> m_tokenTypeToString = {
        {TokenType::BOOL, "logicka_hodnota"},
        {TokenType::FUNCTION, "funkce"},
        {TokenType::LIST, "list"},
        {TokenType::IDENTIFIER, "identifikator"},
        {TokenType::MACRO_FN, "makro"},
        {TokenType::STRING, "retezec"},
        {TokenType::NUMBER, "cislo"}
    };
public:
    GetType();
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &context) override;
};

#endif
