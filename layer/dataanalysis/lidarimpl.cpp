#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidar.h"
#include "common/discretefunction.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

const double LidarImpl::m_edgeTreshold = 0.5;

LidarImpl::LidarImpl(Hardware::Lidar &lidar) :
	m_lidar(lidar)
{ }

LidarObjects LidarImpl::getAllObjects(const Point &ownPosition, double /*ownOrientation*/) const
{
	LidarObjects objects(ownPosition);
	DiscreteFunction distances(0, 360);

	for (size_t i = 0; i <= 360; ++i)
		distances.setValue(i, m_lidar.getDistance(i));

	distances.suppressNoise();
	DiscreteFunction distanceEdges(distances);
	distanceEdges.differentiate(1);
	list<int> positiveEdges = distanceEdges.getPositionsWithValuesAbove(m_edgeTreshold);
	list<int> negativeEdges = distanceEdges.getPositionsWithValuesAbove((-1)*m_edgeTreshold);
	list<pair<int, int> > startAndEndOfObjects = findStartAndEndOfObjects(positiveEdges, negativeEdges);

	return objects;
}

list<pair<int, int> > LidarImpl::findStartAndEndOfObjects(
		const list<int> &/*positiveEdges*/, const list<int> &/*negativeEdges*/) const
{
	list<pair<int, int> > result;
	return result;
}
