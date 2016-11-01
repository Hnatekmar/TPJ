#include <iostream>
#include "include/Lexer.h"

int main()
{
	Lexer lexer(std::cin);
	while(true)
	{
		std::cout << lexer.nextToken().value << std::endl;
	}
	return 0;
}

