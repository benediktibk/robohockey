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

LidarImpl::LidarImpl(Hardware::Lidar &lidar, double minimumDistanceToObstacle, double axisLength, double timeToStop) :
	m_lidar(lidar),
	m_minimumSensorNumber(lidar.getMinimumSensorNumber()),
	m_maximumSensorNumber(lidar.getMaximumSensorNumber()),
	m_minimumDistanceToObstacleAngst(0.05),
	m_minimumDistanceToObstacle(minimumDistanceToObstacle + m_minimumDistanceToObstacleAngst),
	m_edgeTreshold(0.25),
	m_minimumWidthInSensorNumbers(3),
	m_maximumWidthInMeter(0.7),
	m_axisLengthAngst(0.03),
	m_axisLength(axisLength + m_axisLengthAngst),
	m_timeToStop(timeToStop),
	m_lowPassPart(new Common::DiscreteFunction(0, m_maximumSensorNumber)),
	m_highPassPart(new Common::DiscreteFunction(0, m_maximumSensorNumber)),
	m_rawData(new Common::DiscreteFunction(0, m_maximumSensorNumber))
{
	// These values stay the same, therefore we have to calculate them only once.
	initializeMinimumDistancesForCollisionDetection();
}

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
	for (vector<DistanceForSensor>::const_iterator i = m_minimumDistances.begin(); i != m_minimumDistances.end(); ++i)
	{
		unsigned int sensorNumber = i->first;
		double minimumDistance = i->second;
		double distance = m_lowPassPart->getValue(sensorNumber);
		Angle angle = calculateOrientationFromSensorNumber(sensorNumber);
		double brakingDistance = speed*m_timeToStop;
		// The consideration of the braking distance is not totally correct this way, but it should be good enough.
		double totalDistance = minimumDistance + brakingDistance*cos(angle.getValueBetweenMinusPiAndPi());

		if (distance < totalDistance)
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
	list<pair<int, int> > startAndEndOfObjects = findStartAndEndOfObjects(positiveEdges, negativeEdges);

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

		if (object->getWidthInMeter() < m_maximumWidthInMeter && object->getWidthInMeter() >= 0)
			m_objects.push_back(object);
		else
			delete object;
	}
}

list<pair<int, int> > LidarImpl::findStartAndEndOfObjects(
		const list<int> &positiveEdges, const list<int> &negativeEdges) const
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
		return result;

	result.push_back(pair<int, int>(0, allEdges.front()));
	result.push_back(pair<int, int>(allEdges.back(), m_maximumSensorNumber));

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

double LidarImpl::calculateMinimumDistanceToObstacle(const Angle &angle) const
{
	const double anglePositive = fabs(angle.getValueBetweenMinusPiAndPi());
	const double orthogonalDistance = m_axisLength/(2*tan(anglePositive));

	if (orthogonalDistance <= m_minimumDistanceToObstacle)
		return m_axisLength/(2*sin(anglePositive));
	else
		return m_minimumDistanceToObstacle/cos(anglePositive);
}

void LidarImpl::initializeMinimumDistancesForCollisionDetection()
{
	const double possibleBlindAngle = 13*M_PI/180; // more than the necessary 12°, just to be sure
	const unsigned int sensorDistanceToEdges = 30;
	const unsigned int possibleBlindSensorNumberRight = ceil((M_PI/2 + possibleBlindAngle)*361/M_PI);
	const unsigned int possibleBlindSensorNumberLeft = floor((M_PI/2 - possibleBlindAngle)*361/M_PI);
	const size_t capacity = m_maximumSensorNumber - m_minimumSensorNumber - (possibleBlindSensorNumberRight - possibleBlindSensorNumberLeft);
	m_minimumDistances.reserve(capacity);

	assert(possibleBlindSensorNumberRight < m_maximumSensorNumber);
	assert(possibleBlindSensorNumberLeft < m_maximumSensorNumber);

	for (unsigned int i = m_minimumSensorNumber + sensorDistanceToEdges; i < possibleBlindSensorNumberLeft; ++i)
	{
		Angle angle = calculateOrientationFromSensorNumber(i);
		double minimumDistance = calculateMinimumDistanceToObstacle(angle);
		m_minimumDistances.push_back(DistanceForSensor(i, minimumDistance));
	}

	for (unsigned int i = possibleBlindSensorNumberRight; i < m_maximumSensorNumber - sensorDistanceToEdges; ++i)
	{
		Angle angle = calculateOrientationFromSensorNumber(i);
		double minimumDistance = calculateMinimumDistanceToObstacle(angle);
		m_minimumDistances.push_back(DistanceForSensor(i, minimumDistance));
	}

	assert(m_minimumDistances.capacity() <= capacity);
}

void LidarImpl::clearInternalObjects()
{
	for (vector<LidarInternalObject*>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
		delete *i;
	m_objects.clear();
}

double LidarImpl::calculateWidthFromAngleAndDistance(const Angle &angle, double distance)
{
	Compare compare(0.001);

	if (compare.isFuzzyEqual(angle.getValueBetweenMinusPiAndPi(), 0))
		return 0;
	else
		return 2*distance/(1/tan(angle.getValueBetweenMinusPiAndPi()/2) - 1);
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
