#include "layer/autonomous/fieldobjectdistancecompare.h"
#include "layer/autonomous/fieldobject.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldObjectDistanceCompare::FieldObjectDistanceCompare(const Point &position) :
	m_position(position)
{ }

bool FieldObjectDistanceCompare::operator()(const FieldObject &one, const FieldObject &two) const
{
	const Circle &circleOne = one.getCircle();
	const Circle &circleTwo = two.getCircle();
	double distanceOne = circleOne.getDistanceTo(m_position);
	double distanceTwo = circleTwo.getDistanceTo(m_position);
	return distanceOne < distanceTwo;
}
