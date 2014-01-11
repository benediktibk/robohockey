#include "layer/dataanalysis/lidarobjects.h"
#include "layer/dataanalysis/lidarobjectdistancecomparator.h"
#include "common/compare.h"
#include <algorithm>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

void LidarObjects::addObject(const LidarObject &object)
{
	m_objects.push_back(object);
}

vector<LidarObject> LidarObjects::getObjectsWithDistanceBelow(const Point &ownPosition, double distance) const
{
	LidarObject upperBoundObject(ownPosition + Point(distance, 0), 0);
	LidarObjectDistanceComparator comparator(ownPosition);
	vector<LidarObject> objectsSorted = m_objects;
	sort(objectsSorted.begin(), objectsSorted.end(), comparator);
	vector<LidarObject>::iterator lastPosition =
			upper_bound(objectsSorted.begin(), objectsSorted.end(),
						upperBoundObject, comparator);
	return vector<LidarObject>(objectsSorted.begin(), lastPosition);
}

list<LidarObject> LidarObjects::getObjectsInRegionOfInterest(const Rectangle &rectangle) const
{
	list<LidarObject> result;
	Compare compare(0.01);

	for (vector<LidarObject>::const_iterator i = m_objects.begin(); i != m_objects.end(); ++i)
		if (rectangle.overlapsApproximately(*i, compare))
			result.push_back(*i);

	return result;
}

size_t LidarObjects::getObjectCount() const
{
	return m_objects.size();
}

void LidarObjects::clear()
{
	m_objects.clear();
}