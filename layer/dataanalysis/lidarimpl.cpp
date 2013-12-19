#include "layer/dataanalysis/lidarimpl.h"
#include "layer/dataanalysis/lidarinternalobject.h"
#include "layer/hardware/lidar.h"
#include "common/discretefunction.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include <boost/scoped_ptr.hpp>
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;
using namespace boost;

LidarImpl::LidarImpl(Hardware::Lidar &lidar) :
	m_lidar(lidar),
	m_minimumSensorNumber(lidar.getMinimumSensorNumber()),
	m_maximumSensorNumber(lidar.getMaximumSensorNumber()),
	m_edgeTreshold(0.14),
	m_minimumWidthInSensorNumbers(4),
	m_maximumWidthInMeter(0.7),
	m_maximumDistance(4),
	m_lowPassPart(new Common::DiscreteFunction(0, m_maximumSensorNumber)),
	m_highPassPart(new Common::DiscreteFunction(0, m_maximumSensorNumber)),
	m_rawData(new Common::DiscreteFunction(0, m_maximumSensorNumber)),
	m_maximumAngleRight(0),
	m_maximumAngleLeft(0)
{ }

LidarImpl::~LidarImpl()
{
	delete m_highPassPart;
	m_highPassPart = 0;
	delete m_lowPassPart;
	m_lowPassPart = 0;
	delete m_rawData;
	m_rawData = 0;
	clearInternalObjects();
}

LidarObjects LidarImpl::getAllObjects(const RobotPosition &ownPosition) const
{
	LidarObjects objects(ownPosition.getPosition());

	for (vector<LidarInternalObject*>::const_iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		const LidarInternalObject &object = **i;
		Point positionRelativeToRobot = object.getPositionRelativeToRobot();
		positionRelativeToRobot.rotate(ownPosition.getOrientation());
		Point positionOfObject = ownPosition.getPosition() + positionRelativeToRobot;
		objects.addObject(LidarObject(positionOfObject, object.getWidthInMeter()));
	}

	return objects;
}

bool LidarImpl::isObstacleInFront(double speed) const
{
	for (vector<LidarInternalObject*>::const_iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		const LidarInternalObject &object = **i;

		if (object.getWidthInMeter() < 0.12)
			continue;

		const Angle &objectOrientation = object.getOrientationRelativeToRobot();
		double minimumDistance = calculateMinimumDistanceToObstacle(objectOrientation, speed);

		if (object.getDistance() < minimumDistance)
			return true;
	}

	return false;
}

void LidarImpl::updateSensorData()
{
	scoped_ptr<DiscreteFunction> rawData(readInData());
	*m_rawData = *rawData;
	rawData->suppressNoiseLight();
	*m_lowPassPart = *rawData;
	*m_highPassPart = *rawData;
	m_highPassPart->differentiate(1);

	clearInternalObjects();
	list<int> positiveEdges = m_highPassPart->getPositionsWithValuesAbove(m_edgeTreshold);
	list<int> negativeEdges = m_highPassPart->getPositionsWithValuesBelow((-1)*m_edgeTreshold);
	positiveEdges = replaceFollowingEdgesWithBiggestMagnitudePosition(positiveEdges, *m_highPassPart);
	negativeEdges = replaceFollowingEdgesWithBiggestMagnitudePosition(negativeEdges, *m_highPassPart);
	int viewAreaMinimum = 0;
	int viewAreaMaximum = 0;
	list<pair<int, int> > startAndEndOfObjects = findStartAndEndOfObjects(
				positiveEdges, negativeEdges, viewAreaMinimum, viewAreaMaximum);

	m_maximumAngleRight = calculateOrientationFromSensorNumber(viewAreaMinimum);
	m_maximumAngleLeft = calculateOrientationFromSensorNumber(viewAreaMaximum);

	for (list<pair<int, int> >::iterator i = startAndEndOfObjects.begin(); i != startAndEndOfObjects.end(); ++i)
	{
		int start = i->first;
		int end = i->second;
		int widthInSensorNumbers = end - start + 1;
		if (widthInSensorNumbers < m_minimumWidthInSensorNumbers)
			continue;

		double distance = m_rawData->getMinimumInRange(start + 1, end - 1);
		int middleSensorNumber = (end + start)/2;
		Angle orientationOfObjectRelativeToOwnOrientation = calculateOrientationFromSensorNumber(middleSensorNumber);
		Angle widthInAngle = calculateOrientationFromSensorNumber(end - 1) - calculateOrientationFromSensorNumber(start + 1);
		LidarInternalObject *object = new LidarInternalObject(widthInAngle, orientationOfObjectRelativeToOwnOrientation, distance);

		if (	object->getWidthInMeter() < m_maximumWidthInMeter &&
				object->getWidthInMeter() >= 0 &&
				object->getDistance() < m_maximumDistance)
			m_objects.push_back(object);
		else
			delete object;
	}
}

bool LidarImpl::isPuckCollectable(double maximumDistance, const Angle &maximumAngle) const
{
	list<LidarInternalObject*> candidatesForPuckByDistance = getObjectsCloserThan(maximumDistance);
	vector<LidarInternalObject*> candidatesForPuckByAngleAndDistance;

	candidatesForPuckByAngleAndDistance.reserve(candidatesForPuckByDistance.size());
	for (list<LidarInternalObject*>::const_iterator i = candidatesForPuckByDistance.begin(); i != candidatesForPuckByDistance.end(); ++i)
	{
		LidarInternalObject *object = *i;
		Angle objectAngle = object->getOrientationRelativeToRobot();
		if (fabs(objectAngle.getValueBetweenMinusPiAndPi()) < maximumAngle.getValueBetweenMinusPiAndPi())
			candidatesForPuckByAngleAndDistance.push_back(object);
	}

	return candidatesForPuckByAngleAndDistance.size() > 0;
}

bool LidarImpl::isPuckCollected() const
{
	const double maximumDistanceToPuck = 0.197;
	const double maximumAngleToPuck = 5.0/180*M_PI;
	list<LidarInternalObject*> candidatesForPuckByDistance = getObjectsCloserThan(maximumDistanceToPuck);
	vector<LidarInternalObject*> candidatesForPuckByAngleAndDistance;

	candidatesForPuckByAngleAndDistance.reserve(candidatesForPuckByDistance.size());
	for (list<LidarInternalObject*>::const_iterator i = candidatesForPuckByDistance.begin(); i != candidatesForPuckByDistance.end(); ++i)
	{
		LidarInternalObject *object = *i;
		Angle objectAngle = object->getOrientationRelativeToRobot();
		if (fabs(objectAngle.getValueBetweenMinusPiAndPi()) < maximumAngleToPuck)
			candidatesForPuckByAngleAndDistance.push_back(object);
	}

	return candidatesForPuckByAngleAndDistance.size() == 1;
}

Angle LidarImpl::getMaximumAngleRight() const
{
	return m_maximumAngleRight;
}

Angle LidarImpl::getMaximumAngleLeft() const
{
	return m_maximumAngleLeft;
}

bool LidarImpl::canBeSeen(const Circle &object, const RobotPosition &ownPosition) const
{
	const Point &originalCenter = object.getCenter();
	const Point &ownPoint = ownPosition.getPosition();
	Point center = originalCenter - ownPosition.getPosition();
	center.rotate(ownPosition.getOrientation()*(-1));
	Circle movedObject(center, object.getDiameter());
	double distanceToObject = object.getDistanceTo(ownPoint);

	if (distanceToObject > m_maximumDistance)
		return false;

	double distanceToCenter = ownPoint.distanceTo(originalCenter);
	double radius = movedObject.getDiameter()/2;

	if (distanceToCenter < radius)
		return true;

	Compare radiusCompare(0.001);
	if (radiusCompare.isFuzzyEqual(radius, 0))
		return true;

	Angle viewAngleHalf = asin(radius/distanceToCenter);
	Angle orientationOfObject(Point(0, 0), center);
	Angle leftEdge = orientationOfObject + viewAngleHalf;
	Angle rightEdge = orientationOfObject - viewAngleHalf;
	Angle maximumViewAngleLeft = getMaximumAngleLeft() - Angle::convertFromDegreeToRadiant(5);
	Angle maximumViewAngleRight = getMaximumAngleRight() + Angle::convertFromDegreeToRadiant(5);

	if (leftEdge.getValueBetweenMinusPiAndPi() > maximumViewAngleLeft.getValueBetweenMinusPiAndPi())
		leftEdge = maximumViewAngleLeft;
	if (rightEdge.getValueBetweenMinusPiAndPi() < maximumViewAngleRight.getValueBetweenMinusPiAndPi())
		rightEdge = maximumViewAngleRight;

	unsigned int leftEdgeSensorNumber = calculateSensorNumberFromOrientation(leftEdge);
	unsigned int rightEdgeSensorNumber = calculateSensorNumberFromOrientation(rightEdge);
	Compare compare(0.07);

	for (unsigned int i = rightEdgeSensorNumber; i <= leftEdgeSensorNumber; ++i)
	{
		double distanceToObject = calculateDistanceToObject(movedObject, i, distanceToCenter, orientationOfObject);
		double distanceFromSensor = m_rawData->getValue(i);

		if (compare.isFuzzySmaller(distanceToObject, distanceFromSensor))
			return true;
	}

	return false;
}

list<pair<int, int> > LidarImpl::findStartAndEndOfObjects(
		const list<int> &positiveEdges, const list<int> &negativeEdges, int &viewAreaMinimum, int &viewAreaMaximum) const
{
	list<pair<int, int> > result;
	vector<int> allEdges; // true: positive edge; false: negative edge
	list<int>::const_iterator positiveEdgeIterator = positiveEdges.begin();
	list<int>::const_iterator negativeEdgeIterator = negativeEdges.begin();

	while (positiveEdgeIterator != positiveEdges.end() && negativeEdgeIterator != negativeEdges.end())
	{
		int nextPositivePosition = *positiveEdgeIterator;
		int nextNegativePosition = *negativeEdgeIterator;

		if (nextPositivePosition < nextNegativePosition)
		{
			allEdges.push_back(nextPositivePosition);
			++positiveEdgeIterator;
		}
		else
		{
			allEdges.push_back(nextNegativePosition);
			++negativeEdgeIterator;
		}
	}

	if (positiveEdgeIterator != positiveEdges.end())
		for (; positiveEdgeIterator != positiveEdges.end(); ++positiveEdgeIterator)
			allEdges.push_back(*positiveEdgeIterator);
	else
		for (; negativeEdgeIterator != negativeEdges.end(); ++negativeEdgeIterator)
			allEdges.push_back(*negativeEdgeIterator);

	if (allEdges.size() == 0)
	{
		viewAreaMinimum = 0;
		viewAreaMaximum = m_maximumSensorNumber;
		return result;
	}

	viewAreaMinimum = allEdges.front();
	viewAreaMaximum = allEdges.back();

	for (vector<int>::const_iterator i = allEdges.begin(); i != allEdges.end() - 1; ++i)
		result.push_back(pair<int, int>(*i, *(i + 1)));

	return result;
}

DiscreteFunction *LidarImpl::readInData() const
{
	DiscreteFunction *distances = new DiscreteFunction(0, m_maximumSensorNumber);

	for (unsigned int i = m_minimumSensorNumber; i <= m_maximumSensorNumber; ++i)
		distances->setValue(i, m_lidar.getDistance(i));

	return distances;
}

Angle LidarImpl::calculateOrientationFromSensorNumber(unsigned int value) const
{
	double k = M_PI/(static_cast<double>(m_maximumSensorNumber) - m_minimumSensorNumber);
	double d = (-1)*M_PI/2;
	return Angle(value*k + d);
}

unsigned int LidarImpl::calculateSensorNumberFromOrientation(const Angle &angle) const
{
	double k = M_PI/(static_cast<double>(m_maximumSensorNumber) - m_minimumSensorNumber);
	double d = (-1)*M_PI/2;
	int sensorNumber = (angle.getValueBetweenMinusPiAndPi() - d)/k;

	if (sensorNumber < 0)
		sensorNumber = 0;
	else if (sensorNumber > 360)
		sensorNumber = 360;

	return sensorNumber;
}

double LidarImpl::calculateDistanceToObject(
		const Circle &circle, unsigned int sensorNumber, double distanceToCenter, const Angle &angleToCenterOfCircle) const
{
	Compare compare(0.01);
	Angle viewAngle = calculateOrientationFromSensorNumber(sensorNumber) - angleToCenterOfCircle;
	double radius = circle.getDiameter()/2;

	if (compare.isFuzzyEqual(radius, 0) || compare.isFuzzyEqual(viewAngle.getValueBetweenMinusPiAndPi(), 0))
		return distanceToCenter - radius;

	Angle gamma = asin(distanceToCenter/radius*sin(viewAngle.getValueBetweenMinusPiAndPi()));
	Angle angleInCircle = Angle::getHalfRotation() - viewAngle - gamma;
	double distanceToEdgeOfCircle = radius*sin(angleInCircle.getValueBetweenMinusPiAndPi())/sin(viewAngle.getValueBetweenMinusPiAndPi());
	return distanceToEdgeOfCircle;
}

double LidarImpl::calculateMinimumDistanceToObstacle(const Angle &angle, double speed) const
{
	const double anglePositive = fabs(angle.getValueBetweenMinusPiAndPi());
	const double additionalSpaceBesideAxis = 0.05;
	const double axisLength = 0.38 + additionalSpaceBesideAxis;
	const double axisLengthTwice = axisLength*2;
	const double timeToStop = 0.2;
	const double minimumDistanceToObstacle = 0.3 + axisLength + speed*timeToStop;
	const double axisLengthWithAngle = axisLengthTwice*cos(anglePositive);
	const double axisLengthWithAngleSquare = axisLengthWithAngle*axisLengthWithAngle;
	const double minimumWithAngle = minimumDistanceToObstacle*sin(anglePositive);
	const double minimumWithAngleSquare = minimumWithAngle*minimumWithAngle;
	return axisLengthTwice*minimumDistanceToObstacle/(sqrt(axisLengthWithAngleSquare + 4*minimumWithAngleSquare));
}

void LidarImpl::clearInternalObjects()
{
	for (vector<LidarInternalObject*>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
		delete *i;
	m_objects.clear();
}

list<LidarInternalObject*> LidarImpl::getObjectsCloserThan(double distance) const
{
	list<LidarInternalObject*> result;

	for (vector<LidarInternalObject*>::const_iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		LidarInternalObject *object = *i;
		if (object->getDistance() < distance)
			result.push_back(object);
	}

	return result;
}

list<int> LidarImpl::replaceFollowingEdgesWithBiggestMagnitudePosition(const list<int> &edges, const DiscreteFunction &edgeFunction)
{
	list<int> result;

	for (list<int>::const_iterator i = edges.begin(); i != edges.end(); ++i)
	{
		list<int>::const_iterator lastEdgeOfFollowingOnes = i;
		++lastEdgeOfFollowingOnes;
		int lastPosition = *i;

		for (; lastEdgeOfFollowingOnes != edges.end() && *lastEdgeOfFollowingOnes == lastPosition + 1; ++lastEdgeOfFollowingOnes)
			lastPosition = *lastEdgeOfFollowingOnes;

		int biggestMagnitudePosition = *i;
		double biggestMagnitude = fabs(edgeFunction.getValue(*i));
		list<int>::const_iterator j = i;
		++j;
		for (; j != lastEdgeOfFollowingOnes; ++j)
		{
			double magnitude = fabs(edgeFunction.getValue(*j));
			if (magnitude > biggestMagnitude)
			{
				biggestMagnitude = magnitude;
				biggestMagnitudePosition = *j;
			}
		}

		result.push_back(biggestMagnitudePosition);
		--lastEdgeOfFollowingOnes;
		i = lastEdgeOfFollowingOnes;
	}

	return result;
}
