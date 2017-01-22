#include <iostream>
#include <sstream>
#include "include/Lexer.h"
#include "include/Parser.h"

int main()
{
    std::stringstream ss;
    std::string line;
    Parser parser;
    while(std::getline(std::cin, line))
    {
        std::stringstream ss;
        ss << line;
        /*Lexer tokenPrinter(ss);
        while(!tokenPrinter.eof())
        {
            std::cout << tokenPrinter.nextToken() << std::endl;
        }*/
        try
        {
            Lexer lexer(ss);
            parser.parse(lexer, true);
        }
        catch(InterpreterException c)
        {
            std::cerr << "Chyba:" << c.what() << std::endl;
        }
    }
	return 0;
}

