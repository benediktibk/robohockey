#include "layer/autonomous/borderstone.h"

using namespace RoboHockey::Layer::Autonomous;

BorderStone::BorderStone(BorderStoneFieldDistance distanceToFather, BorderStoneDistances &distances, RoboHockey::Common::Point &point):
	Point(point.getX(), point.getY()),
	m_distances(distances),
	m_distanceToFather(distanceToFather)
{ }
