#ifndef TYPE_H
#define TYPE_H

#include <boost/variant.hpp>
#include <list>

typedef boost::make_recursive_variant<float, std::string, bool, std::list<boost::recursive_variant_ > >::type MirageType;

#endif
