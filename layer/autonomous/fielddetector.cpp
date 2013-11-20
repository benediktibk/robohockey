#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/borderstone.h"
#include "common/angle.h"
#include <iostream>
#include <math.h>

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

		// Add One, as root is a BorderStone, too
		int numberOfFoundBorderStones = 1 + root.getNumberOfChildrenRecursive();

		if (numberOfFoundBorderStones > 2)
		{
			cout << "Found " << numberOfFoundBorderStones << " BorderStones!" << endl;
			if (tryToFigureOutNewOrigin(root))
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

bool FieldDetector::tryToFigureOutNewOrigin(BorderStone &root)
{
	BorderStoneDistances distancesChecker;
	BorderStoneFieldDistance firstDistance;
	BorderStoneFieldDistance secondDistance;

	double standardDistanceA = distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceA);
	double standardDistanceB = distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceB);
	double standardDistanceC = distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceC);


	Point cornerOne;
	Point cornerTwo;
	BorderStone *firstChild;
	BorderStone *secondChild;
	bool linear = false;

	if (root.getAllChildren().size() < 2)
	{
		linear = true;
		firstChild = &root.getAllChildren().front();
		secondChild = &firstChild->getAllChildren().front();
		firstDistance = firstChild->getDistanceToFather();
		secondDistance = secondChild->getDistanceToFather();
	} else
	{
		linear = false;
		firstChild = &root.getAllChildren().front();
		secondChild = &root.getAllChildren().back();
		firstDistance = firstChild->getDistanceToFather();
		secondDistance = secondChild->getDistanceToFather();
	}

	if (firstDistance == secondDistance && firstDistance == BorderStoneFieldDistanceC)
	{
		if (linear)
		{
			cornerOne = root +
						((Point(*firstChild) - Point(root)) * (standardDistanceA + standardDistanceB)) / standardDistanceC;
			cornerTwo = root +
						((Point(root) - Point(*firstChild)) * (standardDistanceA + standardDistanceB)) / standardDistanceC;
		} else
		{
			cornerOne = root +
						((Point(*firstChild) - Point(root)) * (standardDistanceA + standardDistanceB + standardDistanceC)) / standardDistanceC;
			cornerTwo = root +
						((Point(root) - Point(*firstChild)) * (standardDistanceA + standardDistanceB + standardDistanceC)) / standardDistanceC;
		}

	}

	Point possibleNewOrigin;

	if (cornerOne.distanceTo(Point()) < cornerTwo.distanceTo(Point()))
		possibleNewOrigin = cornerOne;
	else
		possibleNewOrigin = cornerTwo;

	Point pointOfRoot(root.getX(), root.getY());

	if (!(pointOfRoot == possibleNewOrigin))
	{
		Angle angle(possibleNewOrigin, pointOfRoot);
		m_rotation = -1.0 * angle.getValueBetweenZeroAndTwoPi();
	} else
	{
		Point onePointFound(root.getAllChildren().front().getX(), root.getAllChildren().front().getY());
		Angle angle(possibleNewOrigin, onePointFound);
		m_rotation = -1.0 * angle.getValueBetweenZeroAndTwoPi();
	}

	m_newOrigin = possibleNewOrigin;

	return true;
}
