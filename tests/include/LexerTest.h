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

	SECTION("Pokud již na vstupu nic není lexer vrátí token END_OF_PROGRAM")
	{
		auto token = lexer.nextToken();
		REQUIRE(token.type == TokenType::END_OF_PROGRAM);
		REQUIRE(token.value == "");
	}

	SECTION("Nezávisle na tom, kolikrát se metoda nextToken zavolá")
	{
		auto token = lexer.nextToken();
		REQUIRE(token.type == TokenType::END_OF_PROGRAM);
		REQUIRE(token.value == "");
	}
}

TEST_CASE("Nevalidní vstup", "[lexer]")
{
	std::stringstream ss;
	ss << "["; // Není číslo, identifikátor, řetězec nebo závorka
	Lexer lexer(ss);
	SECTION("V případě nevalidního vstupu bude Lexer vracet token typu INVALID_TOKEN s hodnotou nevalidního vstupu")
	{
		auto token = lexer.nextToken();
		REQUIRE(token.type == TokenType::INVALID_TOKEN);
		REQUIRE(token.value == "[");
	}
}

#endif /* end of include guard: LEXERTEST_H */
