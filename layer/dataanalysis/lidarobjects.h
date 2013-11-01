#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTS_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTS_H

#include "layer/dataanalysis/lidarobject.h"
#include <list>
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObjectDistanceComparator;

	class LidarObjects
	{
	public:
		LidarObjects(const Common::Point &ownPosition);
		~LidarObjects();

		void addObject(const LidarObject &object);
		std::vector<LidarObject> getObjectsWithDistanceBelow(double distance) const;
		size_t getObjectCount() const;

	private:
		// forbid copies (just too lazy to implement)
		LidarObjects(const LidarObjects &) { }
		void operator=(const LidarObjects &) { }

	private:
		Common::Point m_ownPosition;
		std::list<LidarObject> m_objectsSortedByDistance;
		LidarObjectDistanceComparator *m_distanceComparator;
	};
}
}
}

#endif
