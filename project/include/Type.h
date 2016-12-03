#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>
#include <map>
#include <functional>
#include <vector>

class AST;

typedef boost::make_recursive_variant<std::function<boost::recursive_variant_(std::vector<AST>&, 
		std::map<std::string, boost::recursive_variant_>&)>,
		float,
		std::list<boost::recursive_variant_>,
		std::string,
		bool>::type MirageType;

typedef std::map<std::string, MirageType> Context;

#endif
