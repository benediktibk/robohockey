#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidar.h"
#include "common/discretefunction.h"
#include "common/compare.h"
#include <boost/scoped_ptr.hpp>
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;
using namespace boost;

const double LidarImpl::m_edgeTreshold = 0.5;
const int LidarImpl::m_minimumWidthInSensorNumbers = 3;

LidarImpl::LidarImpl(Hardware::Lidar &lidar) :
	m_lidar(lidar),
	m_minimumSensorNumber(lidar.getMinimumSensorNumber()),
	m_maximumSensorNumber(lidar.getMaximumSensorNumber())
{ }

LidarObjects LidarImpl::getAllObjects(const Point &ownPosition, double ownOrientation) const
{
	LidarObjects objects(ownPosition);
	scoped_ptr<DiscreteFunction> distances(readInData());

	distances->suppressNoise();
	DiscreteFunction distanceEdges(*distances);
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

		double distance = distances->getMinimumInRange(start + 1, end - 1);
		int middleSensorNumber = (end + start)/2;
		double orientationOfObjectRelativeToOwnOrientation = calculateOrientationFromSensorNumber(middleSensorNumber);
		double orientationOfObject = ownOrientation - orientationOfObjectRelativeToOwnOrientation;
		double widthInAngle = calculateOrientationFromSensorNumber(end - 1) - calculateOrientationFromSensorNumber(start + 1);
		double widthOfObject = calculateWidthFromAngleAndDistance(widthInAngle, distance);
		double totalDistance = distance + widthOfObject/2;
		Point positionOfObjectRelativeToOwnPosition =
				Point(totalDistance*cos(orientationOfObject), totalDistance*sin(orientationOfObject));
		Point positionOfObject = ownPosition + positionOfObjectRelativeToOwnPosition;
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

double LidarImpl::calculateOrientationFromSensorNumber(unsigned int value) const
{
	return static_cast<double>(value)/(static_cast<double>(m_maximumSensorNumber) - m_minimumSensorNumber)*M_PI - M_PI/2;
}

double LidarImpl::calculateWidthFromAngleAndDistance(double angle, double distance)
{
	Compare compare(0.01);

	if (compare.isFuzzyEqual(angle, 0))
		return 0;
	else
		return 2*distance/(1/tan(angle/2) - 1);
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
