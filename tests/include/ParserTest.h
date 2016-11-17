#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include "../../project/include/Parser.h"
#include <sstream>

TEST_CASE("Testování parseru", "[Parsereer]")
{
	SECTION("Testování jednoduchého případu (definice funkce)")
	{
		std::stringstream ss;
		ss << "(funkce (a x y) (* x y))";
		Lexer lexer(ss);
		Parser parser(lexer);
		REQUIRE_NOTHROW(parser.parse());
	}
}
#endif
