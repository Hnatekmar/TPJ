#include "../include/Type.h"

MirageKind getKind(const MirageType& type)
{
	return static_cast<MirageKind>(type.which());
}
