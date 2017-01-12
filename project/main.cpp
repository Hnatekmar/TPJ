#include <iostream>
#include <fstream>
#include "include/Lexer.h"
#include "include/Parser.h"

int main(int argc, char** argv)
{
	try
    {
        if(argc == 2)
        {
            std::ifstream file;
            file.open(argv[1]);
            Lexer lexer(file);
            Parser parser;
            parser.parse(lexer);
        }
        else if(argc > 2)
        {
            std::cerr << "Musíte specifikovat buď jeden soubor nebo žádný";
            return 1;
        }
        else
        {
            Lexer lexer(std::cin);
            Parser parser;
            parser.parse(lexer);
        }
	}
    catch(InterpreterException c)
    {
        std::cerr << "Chyba:" << c.what() << std::endl;
    }
	return 0;
}

