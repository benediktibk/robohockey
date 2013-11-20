#include "layer/dataanalysis/lidarimpl.h"
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

LidarImpl::LidarImpl(Hardware::Lidar &lidar, double minimumDistanceToObstacle) :
	m_lidar(lidar),
	m_minimumSensorNumber(lidar.getMinimumSensorNumber()),
	m_maximumSensorNumber(lidar.getMaximumSensorNumber()),
	m_minimumDistanceToObstacle(minimumDistanceToObstacle),
	m_edgeTreshold(0.5),
	m_minimumWidthInSensorNumbers(3),
	m_maximumWidthInRadiants(1),
	m_maximumWidthInMeter(0.7)
{ }

LidarObjects LidarImpl::getAllObjects(const RobotPosition &ownPosition) const
{
	LidarObjects objects(ownPosition.getPosition());
	scoped_ptr<DiscreteFunction> distances(readInData());

	DiscreteFunction distanceEdges(*distances);
	distanceEdges.suppressNoise();
	distanceEdges.differentiate(1);
	list<int> positiveEdges = distanceEdges.getPositionsWithValuesAbove(m_edgeTreshold);
	list<int> negativeEdges = distanceEdges.getPositionsWithValuesBelow((-1)*m_edgeTreshold);
	positiveEdges = replaceFollowingEdgesWithMiddlePosition(positiveEdges);
	negativeEdges = replaceFollowingEdgesWithMiddlePosition(negativeEdges);
	list<pair<int, int> > startAndEndOfObjects = findStartAndEndOfObjects(positiveEdges, negativeEdges);

	for (list<pair<int, int> >::iterator i = startAndEndOfObjects.begin(); i != startAndEndOfObjects.end(); ++i)
	{
		int start = i->first;
		int end = i->second;
		int widthInSensorNumbers = end - start + 1;
		if (widthInSensorNumbers < m_minimumWidthInSensorNumbers)
			continue;

		Angle widthInAngle = calculateOrientationFromSensorNumber(end - 1) - calculateOrientationFromSensorNumber(start + 1);
		if (widthInAngle.getValueBetweenZeroAndTwoPi() > m_maximumWidthInRadiants)
			continue;

		distances->suppressNoiseInRange(start + 1, end - 1);
		double distance = distances->getMinimumInRange(start + 1, end - 1);
		int middleSensorNumber = (end + start)/2;
		Angle orientationOfObjectRelativeToOwnOrientation = calculateOrientationFromSensorNumber(middleSensorNumber);
		Angle orientationOfObject = ownPosition.getOrientation() + orientationOfObjectRelativeToOwnOrientation;
		double widthOfObject = calculateWidthFromAngleAndDistance(widthInAngle, distance);

		if (widthOfObject > m_maximumWidthInMeter)
			continue;

		double totalDistance = distance + widthOfObject/2;
		Point positionOfObject = ownPosition.getPosition() + Point(totalDistance, orientationOfObject);
		objects.addObject(LidarObject(positionOfObject, widthOfObject));
	}

	return objects;
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

double LidarImpl::calculateWidthFromAngleAndDistance(const Angle &angle, double distance)
{
	Compare compare(0.01);

	if (compare.isFuzzyEqual(angle.getValueBetweenMinusPiAndPi(), 0))
		return 0;
	else
		return 2*distance/(1/tan(angle.getValueBetweenMinusPiAndPi()/2) - 1);
}

list<int> LidarImpl::replaceFollowingEdgesWithMiddlePosition(const list<int> &edges)
{
	list<int> result;

	for (list<int>::const_iterator i = edges.begin(); i != edges.end(); ++i)
	{
		list<int>::const_iterator lastEdgeOfFollowingOnes = i;
		++lastEdgeOfFollowingOnes;
		int lastPosition = *i;

		for (; lastEdgeOfFollowingOnes != edges.end() && *lastEdgeOfFollowingOnes == lastPosition + 1; ++lastEdgeOfFollowingOnes)
			lastPosition = *lastEdgeOfFollowingOnes;

		--lastEdgeOfFollowingOnes;
		int middlePosition = (*i + *lastEdgeOfFollowingOnes)/2;
		result.push_back(middlePosition);

		i = lastEdgeOfFollowingOnes;
	}

	return result;
}
