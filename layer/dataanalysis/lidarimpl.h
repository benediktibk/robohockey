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
		LidarImpl(Hardware::Lidar &lidar, double minimumDistanceToObstacle, double axisLength, double timeToStop);
		virtual ~LidarImpl();

		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const;
		virtual bool isObstacleInFront(double speed) const;
		virtual void updateSensorData();

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges) const;
		Common::DiscreteFunction* readInData() const;
		Common::Angle calculateOrientationFromSensorNumber(unsigned int value) const;
		double calculateMinimumDistanceToObstacle(const Common::Angle &angle) const;
		void initializeMinimumDistancesForCollisionDetection();

	private:
		static double calculateWidthFromAngleAndDistance(const Common::Angle &angle, double distance);
		static std::list<int> replaceFollowingEdgesWithBiggestMagnitudePosition(const std::list<int> &edges, const Common::DiscreteFunction &edgeFunction);

	private:
		Hardware::Lidar &m_lidar;
		const unsigned int m_minimumSensorNumber;
		const unsigned int m_maximumSensorNumber;
		const double m_minimumDistanceToObstacleAngst;
		const double m_minimumDistanceToObstacle;
		const double m_edgeTreshold;
		const int m_minimumWidthInSensorNumbers;
		const double m_maximumWidthInMeter;
		const double m_axisLengthAngst;
		const double m_axisLength;
		const double m_timeToStop;
		std::vector<DistanceForSensor> m_minimumDistances;
		Common::DiscreteFunction *m_lowPassPart;
		Common::DiscreteFunction *m_highPassPart;
		Common::DiscreteFunction *m_rawData;
	};
}
}
}

#endif
