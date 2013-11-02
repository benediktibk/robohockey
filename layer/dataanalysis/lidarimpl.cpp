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
const int LidarImpl::m_maximumSensorNumber = 360;

LidarImpl::LidarImpl(Hardware::Lidar &lidar) :
	m_lidar(lidar)
{ }

LidarObjects LidarImpl::getAllObjects(const Point &ownPosition, double ownOrientation) const
{
	LidarObjects objects(ownPosition);
	scoped_ptr<DiscreteFunction> distances(readInData());

	distances->suppressNoise();
	DiscreteFunction distanceEdges(*distances);
	distanceEdges.differentiate(1);
	list<int> positiveEdges = distanceEdges.getPositionsWithValuesAbove(m_edgeTreshold);
	list<int> negativeEdges = distanceEdges.getPositionsWithValuesAbove((-1)*m_edgeTreshold);
	list<pair<int, int> > startAndEndOfObjects = findStartAndEndOfObjects(positiveEdges, negativeEdges);

	for (list<pair<int, int> >::iterator i = startAndEndOfObjects.begin(); i != startAndEndOfObjects.end(); ++i)
	{
		int start = i->first;
		int end = i->second;
		double distance = distances->getMinimumInRange(start, end);
		int middleSensorNumber = (end + start)/2;
		double orientationOfObjectRelativeToOwnOrientation = calculateOrientationFromSensorNumber(middleSensorNumber);
		double orientationOfObject = ownOrientation - orientationOfObjectRelativeToOwnOrientation;
		double widthInAngle = calculateOrientationFromSensorNumber(end) - calculateOrientationFromSensorNumber(start);
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
	list<pair<bool, int> > edgeOrientation; // true: positive edge; false: negative edge
	list<int>::const_iterator positiveEdgeIterator = positiveEdges.begin();
	list<int>::const_iterator negativeEdgeIterator = negativeEdges.begin();

	while (positiveEdgeIterator != positiveEdges.end() && negativeEdgeIterator != negativeEdges.end())
	{
		int nextPositivePosition = *positiveEdgeIterator;
		int nextNegativePosition = *negativeEdgeIterator;

		if (nextPositivePosition < nextNegativePosition)
		{
			edgeOrientation.push_back(pair<bool, int>(true, nextPositivePosition));
			++positiveEdgeIterator;
		}
		else
		{
			edgeOrientation.push_back(pair<bool, int>(false, nextNegativePosition));
			++negativeEdgeIterator;
		}
	}

	if (positiveEdgeIterator != positiveEdges.end())
		for (; positiveEdgeIterator != positiveEdges.end(); ++positiveEdgeIterator)
			edgeOrientation.push_back(pair<bool, int>(true, *positiveEdgeIterator));
	else
		for (; negativeEdgeIterator != negativeEdges.end(); ++negativeEdgeIterator)
			edgeOrientation.push_back(pair<bool, int>(false, *negativeEdgeIterator));

	if (edgeOrientation.size() == 0)
		return result;

	pair<bool, int> firstEdge = edgeOrientation.front();
	if (firstEdge.first)
	{
		result.push_back(pair<int, int>(0, firstEdge.second));
		edgeOrientation.pop_front();
	}

	if (edgeOrientation.size() == 0)
		return result;

	pair<bool, int> lastEdge = edgeOrientation.back();
	if (!lastEdge.first)
	{
		result.push_back(pair<int, int>(lastEdge.second, m_maximumSensorNumber));
		edgeOrientation.pop_back();
	}

	while (edgeOrientation.size() > 1)
	{
		pair<bool, int> currentEdge = edgeOrientation.front();

		if (currentEdge.first)
		{
			edgeOrientation.pop_front();
			continue;
		}

		pair<bool, int> nextEdge = *(++edgeOrientation.begin());

		if (!nextEdge.first)
		{
			edgeOrientation.pop_front();
			continue;
		}

		result.push_back(pair<int, int>(currentEdge.second, nextEdge.second));
		edgeOrientation.pop_front();
		edgeOrientation.pop_front();
	}

	return result;
}

DiscreteFunction *LidarImpl::readInData() const
{
	DiscreteFunction *distances = new DiscreteFunction(0, m_maximumSensorNumber);

	for (int i = 0; i <= m_maximumSensorNumber; ++i)
		distances->setValue(i, m_lidar.getDistance(i));

	return distances;
}

double LidarImpl::calculateOrientationFromSensorNumber(int value)
{
	return static_cast<double>(value)/m_maximumSensorNumber*M_PI - M_PI/2;
}

double LidarImpl::calculateWidthFromAngleAndDistance(double angle, double distance)
{
	Compare compare(0.01);

	if (compare.isFuzzyEqual(angle, 0))
		return 0;
	else
		return 2*distance/(1/tan(angle/2) - 1);
}
