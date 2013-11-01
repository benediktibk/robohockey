#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTDISTANCECOMPARATOR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTDISTANCECOMPARATOR_H

#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObject;

	class LidarObjectDistanceComparator
	{
	public:
		LidarObjectDistanceComparator(const Common::Point &ownPosition);

		bool operator()(const LidarObject &one, const LidarObject &two) const;

	private:
		Common::Point m_ownPosition;
	};
}
}
}


#endif
