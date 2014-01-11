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
		void addObject(const LidarObject &object);
		std::vector<LidarObject> getObjectsWithDistanceBelow(const Common::Point &ownPosition, double distance) const;
		std::list<LidarObject> getObjectsInRegionOfInterest(const Common::Rectangle &rectangle) const;
		size_t getObjectCount() const;
		void clear();

	private:
		std::vector<LidarObject> m_objects;
	};
}
}
}

#endif
