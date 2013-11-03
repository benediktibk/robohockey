#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTS_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTS_H

#include "layer/dataanalysis/lidarobject.h"
#include <list>
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Rectangle;
}

namespace Layer
{
namespace DataAnalysis
{
	class LidarObjectDistanceComparator;

	class LidarObjects
	{
	public:
		LidarObjects(const Common::Point &ownPosition);
		LidarObjects(const LidarObjects &objects);
		~LidarObjects();

		void addObject(const LidarObject &object);
		std::vector<LidarObject> getObjectsWithDistanceBelow(double distance) const;
		std::list<LidarObject> getObjectsInRegionOfInterest(const Common::Rectangle &rectangle) const;
		size_t getObjectCount() const;

		void operator=(const LidarObjects &objects);

	private:
		Common::Point m_ownPosition;
		std::list<LidarObject> m_objectsSortedByDistance;
		LidarObjectDistanceComparator *m_distanceComparator;
	};
}
}
}

#endif
