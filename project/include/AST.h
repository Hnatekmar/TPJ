#ifndef AST_H
#define AST_H

#include <vector>
#include <memory>
#include "Token.h"

struct AST
{
	bool call;
	std::shared_ptr<AST> root;
	Token value;
	std::vector<std::shared_ptr<AST>> children; // (1 2) => first := 1, rest := (2)
	AST(Token token, std::shared_ptr<AST>& parent, bool isCall);

	/**
	 * @brief Vyhodnotí strom s ohledem na kontext.
	 * @returns Hodnota výrazu
	 */
	MirageType evaluate(Context& context);
};

#endif
