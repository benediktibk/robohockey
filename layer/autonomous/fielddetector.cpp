#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/borderstone.h"
#include "common/angle.h"
#include "common/rectangle.h"
#include "common/pointdistancecompare.h"
#include <iostream>
#include <math.h>
#include <assert.h>
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetector::FieldDetector():
	m_distanceChecker(0.05),
	m_maxBorderstonesArranged(2),
	m_epsilonBorderStone(0.07)
{ }

bool FieldDetector::tryToDetectField(const Common::Point &currentPosition, std::vector<Common::Point> &pointsOfObjects)
{
	vector<Point*> currentPoints;
	bool result = false;

	for (vector<Point>::iterator i = pointsOfObjects.begin(); i != pointsOfObjects.end(); ++i)
	{
		currentPoints.clear();
		for (vector<Point>::iterator iter = pointsOfObjects.begin(); iter != pointsOfObjects.end(); ++iter)
			if(i != iter)
				currentPoints.push_back(&(*iter));

		BorderStone root(*i, BorderStoneFieldDistanceRoot, m_distanceChecker, *i, m_epsilonBorderStone);
		root.searchNeighbourBorderStones(currentPoints);

		//! Add One, as root is a BorderStone, too
		unsigned int numberOfFoundBorderStones = 1 + root.getNumberOfChildrenRecursive();

		if (numberOfFoundBorderStones > 2)
		{
				result = tryToFigureOutNewOrigin(root, currentPosition) || result;
		}

	}


	return result;
}


Point FieldDetector::getNewOrigin()
{
	return getBestDetectionResult().getTransformationDestination().getPosition();
}

double FieldDetector::getRotation()
{
	return getBestDetectionResult().getTransformationDestination().getOrientation().getValueBetweenMinusPiAndPi();
}

unsigned int FieldDetector::getNumberOfBorderStonesInRow()
{
	if (m_maxBorderstonesArranged < 3)
		return 0;

	return m_maxBorderstonesArranged;
}

bool FieldDetector::tryToFigureOutNewOrigin(BorderStone &root, const Point &currentPosition)
{
	Rectangle fieldGround(Point(0,0), Point(5,3));
	BorderStoneDistances &distancesChecker = m_distanceChecker;
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

	Point currentPositionInNewCoordinates = currentPosition - possibleNewOrigin;
	currentPositionInNewCoordinates.rotate(rotation);

	bool isOpposite = false;

	if (currentPositionInNewCoordinates.getY() < 0)
	{
		Point oppositeOrigin = Point(0,-1* distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceD));
		oppositeOrigin.rotate(Angle( -1* rotation));
		possibleNewOrigin = possibleNewOrigin + oppositeOrigin;
		isOpposite = true;
	}

	currentPositionInNewCoordinates = currentPosition - possibleNewOrigin;
	currentPositionInNewCoordinates.rotate(rotation);

	if (!fieldGround.isInside(currentPositionInNewCoordinates, Compare(0.1)) || !verifyNewOriginWithRoot(possibleNewOrigin, rotation, root))
	{
		return false;
	}

	if (root.getNumberOfChildrenRecursive() + 1 > m_maxBorderstonesArranged)
	{
		m_rotation = rotation;
		m_newOrigin = possibleNewOrigin;
		m_maxBorderstonesArranged = root.getNumberOfChildrenRecursive() + 1;
	}

	RobotPosition newOrigin(possibleNewOrigin, Angle(rotation));

	if (isResultAlreadyKnown(newOrigin))
		getDetectionResultWithNewOrigin(newOrigin).confirmDetectionResultWithPosition(newOrigin, root.getNumberOfChildrenRecursive() + 1, isOpposite);
	else
	{
		m_detectionResults.push_back(FieldDetectionResult(newOrigin, root.getNumberOfChildrenRecursive() + 1, isOpposite));
	}

	return true;
}


bool FieldDetector::verifyNewOriginWithRoot(Common::Point &newOrigin, double , BorderStone &root)
{
	vector<Point> orderedPositions = orderBorderstonesByDistanceToRoot(root, newOrigin);

	if (!m_distanceChecker.verifyPoints(orderedPositions))
		return false;

	return true;
}

vector<Point> FieldDetector::orderBorderstonesByDistanceToRoot(BorderStone &borderstone, Common::Point &root)
{
	vector<Point> result = borderstone.getPointsOfAllNodesInTreeRecursive();

	sort(result.begin(), result.end(), PointDistanceCompare(root));

	return result;
}

bool FieldDetector::isResultAlreadyKnown(RobotPosition &newOrigin)
{
	for (list<FieldDetectionResult>::const_iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).isEqualDetectionResult(newOrigin))
			return true;
	}

	return false;
}

FieldDetectionResult &FieldDetector::getDetectionResultWithNewOrigin(RobotPosition &newOrigin)
{
	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).isEqualDetectionResult(newOrigin))
			return *it;
	}

	return m_detectionResults.back();
}

FieldDetectionResult &FieldDetector::getBestDetectionResult()
{
	unsigned int highestValue = 0;

	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).isConfirmedByBothSides())
			return *it;
		highestValue = max(highestValue, (*it).getNumberOfBorderStones());
	}

	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).getNumberOfBorderStones() == highestValue)
			return *it;
	}

	return m_detectionResults.back();

}

bool FieldDetector::doesConfirmedResultExist()
{
	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).isConfirmedByBothSides())
			return true;
	}

	return false;
}
