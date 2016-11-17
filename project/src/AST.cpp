#include "../include/AST.h"

bool AST::operator==(const AST& right)
{
	if(type == right.type)
	{
		if(value == right.value)
		{
			if(children.size() == right.children.size())
			{
				for(size_t i = 0; i < children.size(); i++)
				{
					if(!(children.at(i) == right.children.at(i)))
					{
						return false;
					}
				}
				return true;
			}
		}
	}
	return false;
}
