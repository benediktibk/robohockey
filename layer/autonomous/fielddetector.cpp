#include "layer/autonomous/fielddetector.h"
#include "layer/autonomous/borderstone.h"
#include "common/angle.h"
#include "common/rectangle.h"
#include "common/pointdistancecompare.h"
#include "common/logger.h"
#include <iostream>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldDetector::FieldDetector(Logger &logger):
	m_logger(logger),
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

	logCurrentCalibrationResults();
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

	vector<Point> stoneVector = orderBorderstonesByDistanceToRoot(root, root);

	Point &first = stoneVector.front();
	Point &last = stoneVector.back();

	Point possibleNewOrigin = first;
	Angle rotation = Angle() - Angle(first, last);

	Point offset(2*distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceA)
				 + 2*distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceB)
				 + 2*distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceC)
				 ,0);
	offset.rotate(Angle() - rotation);
	Point oppositeOrigin = possibleNewOrigin + offset;

	if (currentPosition.distanceTo(oppositeOrigin) < currentPosition.distanceTo(possibleNewOrigin))
	{
		possibleNewOrigin = oppositeOrigin;
		rotation = Angle() - Angle(possibleNewOrigin, last);
	}

	Point currentPositionInNewCoordinates = currentPosition - possibleNewOrigin;
	currentPositionInNewCoordinates.rotate(rotation);

	bool isOpposite = false;

	if (currentPositionInNewCoordinates.getY() < 0)
	{
		Point oppositeOrigin = Point(0,-1* distancesChecker.getStandardFieldDistance(BorderStoneFieldDistanceD));
		oppositeOrigin.rotate(Angle() - rotation);
		possibleNewOrigin = possibleNewOrigin + oppositeOrigin;
		isOpposite = true;
	}

	currentPositionInNewCoordinates = currentPosition - possibleNewOrigin;
	currentPositionInNewCoordinates.rotate(rotation);

	if (!fieldGround.isInside(currentPositionInNewCoordinates, Compare(0.1))
			|| !verifyNewOriginWithRoot(possibleNewOrigin, rotation.getValueBetweenMinusPiAndPi(), root))
	{
		return false;
	}

	if (root.getNumberOfChildrenRecursive() + 1 > m_maxBorderstonesArranged)
	{
		m_rotation = rotation.getValueBetweenMinusPiAndPi();
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

void FieldDetector::logCurrentCalibrationResults()
{
	m_logger.logToLogFileOfType(Logger::LogFileTypeFieldDetection, "BEGIN: Calibration Results");

	unsigned int counter = 0;
	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		string confirmed;
		if ((*it).isConfirmedByBothSides())
			confirmed = "TRUE";
		else
			confirmed = "FALSE";

		stringstream message;
		message << "\tresult #" << counter << ":\n\tOrigin: " << (*it).getTransformationDestination()
				<< "\n\tNumber Borderstones: " << (*it).getNumberOfBorderStones()
				<< " (Near: " << (*it).numberOfNearStones() << ", Far: " << (*it).numberOfOppositeStones() << ")"
				<< "\n\tConfirmed: " << confirmed << endl;

		m_logger.logToLogFileOfType(Logger::LogFileTypeFieldDetection, message.str());
		counter++;
	}

	m_logger.logToLogFileOfType(Logger::LogFileTypeFieldDetection, "END: Calibration Results");

}

bool FieldDetector::hasConfirmedResult()
{
	for (list<FieldDetectionResult>::iterator it = m_detectionResults.begin(); it != m_detectionResults.end(); ++it)
	{
		if ((*it).isConfirmedByBothSides())
			return true;
	}

	return false;
}
