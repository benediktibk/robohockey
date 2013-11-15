#include "layer/autonomous/borderstone.h"
#include "common/compare.h"
#include "math.h"

using namespace std;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

BorderStone::BorderStone(Point &father, BorderStoneFieldDistance distanceToFather, BorderStoneDistances &distances, RoboHockey::Common::Point &point):
	Point(point.getX(), point.getY()),
	m_distances(distances),
	m_father(father),
	m_distanceToFather(distanceToFather)
{ }

void BorderStone::searchNeighbourBorderStones(std::vector<Point*> &candidates)
{
	Compare compare(0.04);

	for (vector<Point*>::iterator i = candidates.begin(); i != candidates.end(); ++i)
	{
		if(m_distances.isDistanceStandardDistance(this->distanceTo(**i)))
		{
			BorderStoneFieldDistance type = m_distances.getStandardDistanceType(this->distanceTo(**i));

			double distanceDirect = m_father.distanceTo(**i);
			double distanceViaThis = m_father.distanceTo(*this) + this->distanceTo(**i);
//			double distanceHypotenuse = sqrt(m_father.distanceTo(*this) * m_father.distanceTo(*this) + this->distanceTo(**i) * this->distanceTo(**i));

			if((compare.isFuzzyEqual(distanceDirect, distanceViaThis) && type != BorderStoneFieldDistanceD)
//					|| (compare.isFuzzyEqual(distanceDirect, distanceHypotenuse) && type == BorderStoneFieldDistanceD)
					)
			{
				m_children.push_back(BorderStone(*this, type, m_distances, **i));
				candidates.erase(i);
				i--;
			}
		}
	}

	for (vector<BorderStone>::iterator i = m_children.begin(); i != m_children.end(); ++i)
	{
		(*i).searchNeighbourBorderStones(candidates);
	}
}

std::vector<BorderStone> &BorderStone::getAllChildren()
{
	return m_children;
}

int BorderStone::getNumberOfChildrenRecursive()
{
	int result = 0;

	for (vector<BorderStone>::iterator i = m_children.begin(); i != m_children.end(); ++i)
	{
		result += (*i).getNumberOfChildrenRecursive();
	}

	result += m_children.size();

	return result;
}
