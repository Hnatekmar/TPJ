#ifndef FUNCTION_H
#define FUNCTION_H

#include "AST.h"

class Function
{

	Parser& m_parser;
	public:
		Function(Context& ctx, std::list<std::shared_ptr<AST>>& args);
};

#endif
