#ifndef AST_TEST_H
#define AST_TEST_H

#include "../../project/include/AST.h"

TEST_CASE("Porovnávání ast", "[AST]")
{
	SECTION("Nejdříve je třeba otestovat, zda funguje porovnávání jednotlivých listů")
	{
		AST ast{ASTType::CALL, "foo"};
		AST ast2{ASTType::ROOT, "foo"};
		AST ast3{ASTType::CALL, "foo"};
		REQUIRE(ast == ast);
		REQUIRE(!(ast == ast2));
		REQUIRE(ast == ast3);
		ast.children.push_back(ast2);
		REQUIRE(ast == ast);
	}
}

#endif
