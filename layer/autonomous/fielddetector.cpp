#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/borderstone.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetector::FieldDetector(vector<Point> &points):
	m_points(points)
{ }

bool FieldDetector::tryToDetectField()
{
	vector<Point*> currentPoints;

	for (vector<Point>::iterator i = m_points.begin(); i != m_points.end(); ++i)
	{
		currentPoints.clear();
		for (vector<Point>::iterator iter = m_points.begin(); iter != m_points.end(); ++iter)
			if(i != iter)
				currentPoints.push_back(&(*iter));

		BorderStone root(*i, BorderStoneFieldDistanceRoot, m_distanceChecker, *i);
		root.searchNeighbourBorderStones(currentPoints);
		int numberOfFoundBorderStones = root.getNumberOfChildrenRecursive();

		if (numberOfFoundBorderStones > 2)
		{
			return true;
		}

	}


	return false;
}


Point FieldDetector::getNewOrigin()
{
	return m_newOrigin;
}

double FieldDetector::getRotation()
{
	return m_rotation;
}
