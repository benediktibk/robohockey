#include "layer/autonomous/borderstone.h"
#include "common/compare.h"
#include "math.h"

using namespace std;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

BorderStone::BorderStone(Point &father, BorderStoneFieldDistance distanceToFather, BorderStoneDistances &distances, Point &point, double epsilon):
	Point(point.getX(), point.getY()),
	m_distances(distances),
	m_father(father),
	m_distanceToFather(distanceToFather),
	m_epsilon(epsilon)
{ }

void BorderStone::searchNeighbourBorderStones(std::vector<Point*> &candidates)
{
	Compare compare(m_epsilon);

	for (vector<Point*>::iterator i = candidates.begin(); i != candidates.end(); ++i)
	{
		if (getAllChildren().size() > (size_t) 0)
			break;

		if(m_distances.isDistanceStandardDistance(this->distanceTo(**i)))
		{
			BorderStoneFieldDistance currentFieldDistance = m_distances.getStandardDistanceType(this->distanceTo(**i));

			if (	(m_distanceToFather == BorderStoneFieldDistanceRoot && currentFieldDistance == BorderStoneFieldDistanceA)
					|| (m_distanceToFather == BorderStoneFieldDistanceA && currentFieldDistance == BorderStoneFieldDistanceB)
					|| (m_distanceToFather == BorderStoneFieldDistanceB && currentFieldDistance == BorderStoneFieldDistanceC)
					|| (m_distanceToFather == BorderStoneFieldDistanceC && currentFieldDistance == BorderStoneFieldDistanceC)
				)
			{
				BorderStoneFieldDistance type = m_distances.getStandardDistanceType(this->distanceTo(**i));

				double distanceDirect = m_father.distanceTo(**i);
				double distanceViaThis = m_father.distanceTo(*this) + this->distanceTo(**i);

				if((compare.isFuzzyEqual(distanceDirect, distanceViaThis) && type != BorderStoneFieldDistanceD))
				{
					m_children.push_back(BorderStone(*this, type, m_distances, **i, m_epsilon));
					candidates.erase(i);
					--i;
				}
			}
		}
	}

	for (vector<BorderStone>::iterator i = m_children.begin(); i != m_children.end(); ++i)
		(*i).searchNeighbourBorderStones(candidates);
}

std::vector<BorderStone> &BorderStone::getAllChildren()
{
	return m_children;
}

std::vector<Point> BorderStone::getPointsOfAllNodesInTreeRecursive()
{
	vector<Point> result;

	for (vector<BorderStone>::iterator i = m_children.begin(); i != m_children.end(); ++i)
	{
		vector<Point> childrenResult = (*i).getPointsOfAllNodesInTreeRecursive();
		result.insert(result.end(), childrenResult.begin(), childrenResult.end());
	}

	result.push_back(Point(getX(), getY()));

	return result;
}

unsigned int BorderStone::getNumberOfChildrenRecursive()
{
	unsigned int result = 0;

	for (vector<BorderStone>::iterator i = m_children.begin(); i != m_children.end(); ++i)
	{
		result += (*i).getNumberOfChildrenRecursive();
	}

	result += m_children.size();

	return result;
}

BorderStoneFieldDistance BorderStone::getDistanceToFather()
{
	return m_distanceToFather;
}
