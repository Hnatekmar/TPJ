#include <iostream>
#include "include/Lexer.h"
#include "include/Parser.h"

int main(int , char** )
{
	try
	{
		Lexer lexer(std::cin);
		Parser parser(lexer);
		parser.parse();
	}
    catch(InterpreterException c)
    {
        std::cout << "Chyba:" << c.what() << std::endl;
	}
	return 0;
}

