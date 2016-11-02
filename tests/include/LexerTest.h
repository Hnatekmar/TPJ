#ifndef LEXERTEST_H
#define LEXERTEST_H

#include "../../project/include/Lexer.h"
#include <sstream>

TEST_CASE("Validní vstup", "[lexer]")
{
	std::stringstream ss;
	ss << "(identifikator 456  \"a retezec\")";
	Lexer lexer(ss);
	SECTION("Při každém zavolání vráti lexer nový token odpovídající vstupu")
	{
		auto token = lexer.nextToken();
		REQUIRE(token.type == TokenType::L_PAREN);
		REQUIRE(token.value == "(");
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::IDENTIFIER);
		REQUIRE(token.value == "identifikator");
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::NUMBER);
		REQUIRE(token.value == "456");
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::STRING);
		REQUIRE(token.value == "a retezec");
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::R_PAREN);
		REQUIRE(token.value == ")");
	}
}

#endif /* end of include guard: LEXERTEST_H */
