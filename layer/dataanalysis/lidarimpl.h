#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Common
{
	class DiscreteFunction;
}

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

		virtual LidarObjects getAllObjects(const Common::Point &ownPosition, double ownOrientation) const;

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges) const;
		Common::DiscreteFunction* readInData() const;

	private:
		static double calculateOrientationFromSensorNumber(int value);
		static double calculateWidthFromAngleAndDistance(double angle, double distance);
		static std::list<int> replaceFollowingEdgesWithMiddlePosition(const std::list<int> &edges);

	private:
		Hardware::Lidar &m_lidar;

	private:
		static const double m_edgeTreshold;
		static const int m_maximumSensorNumber;
	};
}
}
}

#endif
