#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/borderstone.h"
#include "common/angle.h"
#include <iostream>
#include <math.h>
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetector::FieldDetector(const Point &currentPosition, vector<Point> &pointsOfObjects):
	m_currentPosition(currentPosition),
	m_points(pointsOfObjects),
	m_maxBorderstonesArranged(2)
{ }

bool FieldDetector::tryToDetectField()
{
	vector<Point*> currentPoints;
	bool result = false;

	for (vector<Point>::iterator i = m_points.begin(); i != m_points.end(); ++i)
	{
		currentPoints.clear();
		for (vector<Point>::iterator iter = m_points.begin(); iter != m_points.end(); ++iter)
			if(i != iter)
				currentPoints.push_back(&(*iter));

		BorderStone root(*i, BorderStoneFieldDistanceRoot, m_distanceChecker, *i);
		root.searchNeighbourBorderStones(currentPoints);

		//! Add One, as root is a BorderStone, too
		unsigned int numberOfFoundBorderStones = 1 + root.getNumberOfChildrenRecursive();

		if (numberOfFoundBorderStones > 2)
		{
				result = tryToFigureOutNewOrigin(root) || result;

//				if (result)
//					return true;
		}

	}


	return result;
}


Point FieldDetector::getNewOrigin()
{
	assert(m_newOrigins.size() != (size_t) 0);

	Point medianPoint;

	for (vector<RobotPosition>::const_iterator it = m_newOrigins.begin(); it != m_newOrigins.end(); ++it)
		medianPoint = medianPoint + (*it).getPosition() * 1.0/(double) m_newOrigins.size();

//	return medianPoint;
	return m_newOrigin;
}

double FieldDetector::getRotation()
{
	assert(m_newOrigins.size() != (size_t) 0);

	Angle medianRotation;

	for (vector<RobotPosition>::const_iterator it = m_newOrigins.begin(); it != m_newOrigins.end(); ++it)
		medianRotation = medianRotation + (*it).getOrientation() * 1.0/(double) m_newOrigins.size();

//	return medianRotation.getValueBetweenMinusPiAndPi();
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

	Point normFromRoot = (Point(*firstChild) - Point(root)) / distancesChecker.getStandardFieldDistance(firstDistance);
	Point normToRoot = (Point(root) - Point(*firstChild)) / distancesChecker.getStandardFieldDistance(firstDistance);


	if (firstDistance == secondDistance && firstDistance == BorderStoneFieldDistanceC)
	{
		if (linear)
		{
			cornerOne = root + normFromRoot * (standardDistanceA + standardDistanceB + standardDistanceC * 2);
			cornerTwo = root + normToRoot * (standardDistanceA + standardDistanceB);
		} else
		{
			cornerOne = root + normFromRoot * (standardDistanceA + standardDistanceB + standardDistanceC);
			cornerTwo = root + normToRoot * (standardDistanceA + standardDistanceB + standardDistanceC);
		}

	} else if (firstDistance == BorderStoneFieldDistanceB && secondDistance == BorderStoneFieldDistanceC)
	{
		if (linear)
		{
			cornerOne = root + normFromRoot * (standardDistanceA + 2*standardDistanceB + 2*standardDistanceC);
			cornerTwo = root + normToRoot * (standardDistanceA);
		} else
		{
			cornerOne = root + normFromRoot * (standardDistanceB + standardDistanceA);
			cornerTwo = root + normToRoot * (2*standardDistanceC + standardDistanceB + standardDistanceA);
		}
	} else if (firstDistance == BorderStoneFieldDistanceC && secondDistance == BorderStoneFieldDistanceB)
	{
		if (linear)
		{
			cornerOne = root + normFromRoot * (standardDistanceC + standardDistanceB + standardDistanceA);
			cornerTwo = root + normToRoot * (standardDistanceC + standardDistanceB + standardDistanceA);
		} else
		{
			cornerOne = root + normFromRoot * (2*standardDistanceC + standardDistanceB + standardDistanceA);
			cornerTwo = root + normToRoot * (standardDistanceB + standardDistanceA);
		}
	} else if (firstDistance == BorderStoneFieldDistanceA && secondDistance == BorderStoneFieldDistanceB)
	{
		if (linear)
		{
			cornerOne = root + normFromRoot * (2*standardDistanceA + 2*standardDistanceB + 2*standardDistanceC);
			cornerTwo = root;
		} else
		{
			cornerOne = root + normFromRoot * (standardDistanceA);
			cornerTwo = root + normToRoot * (2*standardDistanceB + 2*standardDistanceC + standardDistanceA);
		}
	} else if (firstDistance == BorderStoneFieldDistanceB && secondDistance == BorderStoneFieldDistanceA)
	{
		if (linear)
		{
			cornerOne = root + normFromRoot * (standardDistanceA + standardDistanceB);
			cornerTwo = root + normToRoot * (standardDistanceA + standardDistanceB + 2*standardDistanceC);
		} else
		{
			cornerOne = root + normFromRoot * (2*standardDistanceC + 2*standardDistanceB + standardDistanceA);
			cornerTwo = root + normToRoot * (standardDistanceA);
		}
	} else
	{
		return false;
	}

	Point possibleNewOrigin;

	if (cornerOne.distanceTo(Point()) < cornerTwo.distanceTo(Point()))
		possibleNewOrigin = cornerOne;
	else
		possibleNewOrigin = cornerTwo;

	Point pointOfRoot(root.getX(), root.getY());
	double rotation = 0.0;

	if (!(pointOfRoot == possibleNewOrigin))
	{
		Angle angle(possibleNewOrigin, pointOfRoot);
		rotation = -1.0 * angle.getValueBetweenMinusPiAndPi();
	} else
	{
		Point onePointFound(root.getAllChildren().front().getX(), root.getAllChildren().front().getY());
		Angle angle(possibleNewOrigin, onePointFound);
		rotation = -1.0 * angle.getValueBetweenMinusPiAndPi();
	}

	Point currentPositionInNewCoordinates = m_currentPosition - possibleNewOrigin;
	currentPositionInNewCoordinates.rotate(m_rotation);

	if (currentPositionInNewCoordinates.getY() < 0)
	{
		Point oppositeOrigin = Point(0,-1* distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceD));
		oppositeOrigin.rotate(Angle( -1* m_rotation));
		possibleNewOrigin = possibleNewOrigin + oppositeOrigin;
	}

	m_newOrigins.push_back( RobotPosition( possibleNewOrigin, rotation) );

	if (root.getNumberOfChildrenRecursive() + 1 > m_maxBorderstonesArranged)
	{
		m_rotation = rotation;
		m_newOrigin = possibleNewOrigin;
		m_maxBorderstonesArranged = root.getNumberOfChildrenRecursive() + 1;
	}

	return true;
}
