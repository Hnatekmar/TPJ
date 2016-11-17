#ifndef LEXERTEST_H
#define LEXERTEST_H

#include "../../project/include/Lexer.h"
#include <sstream>

TEST_CASE("Validní vstup", "[lexer]")
{
	std::stringstream ss;
	ss << "(identifikator 456 \"a retezec\")";
	Lexer lexer(ss);
	SECTION("Při každém zavolání vráti lexer nový token odpovídající vstupu")
	{
		auto token = lexer.nextToken();
		REQUIRE(token.type == TokenType::L_PAREN);
		REQUIRE(boost::get<std::string>(token.value) == std::string("("));
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::IDENTIFIER);
		REQUIRE(boost::get<std::string>(token.value) == std::string("identifikator"));
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::NUMBER);
		REQUIRE(boost::get<double>(token.value) == static_cast<double>(456.0));
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::STRING);
		REQUIRE(boost::get<std::string>(token.value) == std::string("a retezec"));
		token = lexer.nextToken();
		REQUIRE(token.type == TokenType::R_PAREN);
		REQUIRE(boost::get<std::string>(token.value) == std::string(")"));
	}
}

#endif /* end of include guard: LEXERTEST_H */
