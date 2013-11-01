#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Lidar;
}

namespace DataAnalysis
{
	class LidarImpl :
			public Lidar
	{
	public:
		LidarImpl(Hardware::Lidar &lidar);

		virtual LidarObjects getAllObjects(const Common::Point &ownPosition) const;

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges) const;

	private:
		Hardware::Lidar &m_lidar;

	private:
		static const double m_edgeTreshold;
	};
}
}
}

#endif
