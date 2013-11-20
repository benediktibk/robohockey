#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"
#include <vector>
#include <utility>

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
	private:
		typedef std::pair<unsigned int, double> DistanceForSensor;

	public:
		LidarImpl(Hardware::Lidar &lidar, double minimumDistanceToObstacle, double axisLength);

		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const;
		virtual bool isObstacleInFront() const;

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges) const;
		Common::DiscreteFunction* readInData() const;
		Common::Angle calculateOrientationFromSensorNumber(unsigned int value) const;
		double calculateMinimumDistanceToObstacle(const Common::Angle &angle) const;

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
		const double m_axisLength;
		std::vector<DistanceForSensor> m_minimumDistances;
	};
}
}
}

#endif
