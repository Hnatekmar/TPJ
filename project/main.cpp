#include <iostream>
#include <map>
#include "include/Lexer.h"

int main()
{
	std::map<TokenType, std::string> translator;
	translator[TokenType::L_PAREN] = "levá závorka";
	translator[TokenType::R_PAREN] = "pravá závorka";
	translator[TokenType::IDENTIFIER] = "identifikator";
	translator[TokenType::NUMBER] = "číslo";
	translator[TokenType::STRING] = "řetězec";
	translator[TokenType::END_OF_PROGRAM] = "Konec programu";
	Lexer lexer(std::cin);
	while(!lexer.eof())
	{
		auto token = lexer.nextToken();
		std::cout << token.value << " Typ: " << translator[token.type] << std::endl;
	}
	return 0;
}

