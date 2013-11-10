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
		double calculateOrientationFromSensorNumber(unsigned int value) const;

	private:
		static double calculateWidthFromAngleAndDistance(double angle, double distance);
		static std::list<int> replaceFollowingEdgesWithMiddlePosition(const std::list<int> &edges);

	private:
		Hardware::Lidar &m_lidar;
		unsigned int m_minimumSensorNumber;
		unsigned int m_maximumSensorNumber;

	private:
		static const double m_edgeTreshold;
		static const int m_minimumWidthInSensorNumbers;
		static const double m_maximumWidthInRadiants;
	};
}
}
}

#endif
