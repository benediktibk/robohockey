#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Common
{
	class DiscreteFunction;
	class Angle;
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
		LidarImpl(Hardware::Lidar &lidar, double minimumDistanceToObstacle);

		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const;

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges) const;
		Common::DiscreteFunction* readInData() const;
		Common::Angle calculateOrientationFromSensorNumber(unsigned int value) const;

	private:
		static double calculateWidthFromAngleAndDistance(const Common::Angle &angle, double distance);
		static std::list<int> replaceFollowingEdgesWithMiddlePosition(const std::list<int> &edges);

	private:
		Hardware::Lidar &m_lidar;
		const unsigned int m_minimumSensorNumber;
		const unsigned int m_maximumSensorNumber;
		const double m_minimumDistanceToObstacle;
		const double m_edgeTreshold;
		const int m_minimumWidthInSensorNumbers;
		const double m_maximumWidthInRadiants;
		const double m_maximumWidthInMeter;
	};
}
}
}

#endif
