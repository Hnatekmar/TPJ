#include <iostream>
#include <map>
#include "include/Lexer.h"
#include "include/Parser.h"

int main()
{
	try
	{
		Lexer lexer(std::cin);
		Parser parser(lexer);
		parser.parse();
	}
	catch(CompilerException c)
	{
		std::cout << "V průběhu kompilace nastala chyba: " << c.what() << std::endl;
	}
	return 0;
}

