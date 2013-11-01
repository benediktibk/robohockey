#include "layer/dataanalysis/lidarobjects.h"
#include "layer/dataanalysis/lidarobjectdistancecomparator.h"
#include <algorithm>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

LidarObjects::LidarObjects(const RoboHockey::Common::Point &ownPosition) :
	m_ownPosition(ownPosition),
	m_distanceComparator(new LidarObjectDistanceComparator(m_ownPosition))
{ }

LidarObjects::LidarObjects(const LidarObjects &objects) :
	m_ownPosition(objects.m_ownPosition),
	m_objectsSortedByDistance(objects.m_objectsSortedByDistance),
	m_distanceComparator(new LidarObjectDistanceComparator(m_ownPosition))
{ }

LidarObjects::~LidarObjects()
{
	delete m_distanceComparator;
}

void LidarObjects::addObject(const LidarObject &object)
{
	list<LidarObject>::iterator position =
			upper_bound(m_objectsSortedByDistance.begin(), m_objectsSortedByDistance.end(),
						object, *m_distanceComparator);
	m_objectsSortedByDistance.insert(position, object);
}

vector<LidarObject> LidarObjects::getObjectsWithDistanceBelow(double distance) const
{
	LidarObject upperBoundObject(m_ownPosition + Point(distance, 0), 0);
	list<LidarObject>::const_iterator lastPosition =
			upper_bound(m_objectsSortedByDistance.begin(), m_objectsSortedByDistance.end(),
						upperBoundObject, *m_distanceComparator);
	return vector<LidarObject>(m_objectsSortedByDistance.begin(), lastPosition);
}

size_t LidarObjects::getObjectCount() const
{
	return m_objectsSortedByDistance.size();
}

void LidarObjects::operator=(const LidarObjects &objects)
{
	m_ownPosition = objects.m_ownPosition;
	m_objectsSortedByDistance = objects.m_objectsSortedByDistance;
}
