#ifndef AST_H
#define AST_H

#include <vector>
#include <memory>
#include "Token.h"

Token evaluateIdentifier(Token identifier, const Context& context);

struct AST
{
	bool call;
	std::shared_ptr<AST> root;
	Token value;
	AST(Token token, std::shared_ptr<AST>& parent, bool isCall);
	std::vector<std::shared_ptr<AST>> children;

	/**
	 * @brief Vyhodnotí strom s ohledem na kontext.
	 * @returns Hodnota výrazu
	 */
     Token evaluate(Context& context);
};

#endif
