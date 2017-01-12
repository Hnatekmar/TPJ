#include <iostream>
#include <sstream>
#include "include/Lexer.h"
#include "include/Parser.h"

int main()
{
	try
	{
        std::stringstream ss;
        std::string line;
        Parser parser;
        while(std::getline(std::cin, line))
        {
            std::cout << "> ";
            std::stringstream ss;
            ss << line;
            Lexer lexer(ss);
            parser.parse(lexer, true);
        }
	}
	catch(InterpreterException c)
	{
		std::cerr << "Chyba:" << c.what() << std::endl;
	}
	return 0;
}

