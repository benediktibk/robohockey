#include "layer/autonomous/fieldobjectcolorcompare.h"
#include "layer/autonomous/fieldobject.h"

using namespace RoboHockey::Layer::Autonomous;

bool FieldObjectColorCompare::operator()(const FieldObject &one, const FieldObject &two) const
{
	return one.getColor() < two.getColor();
}
