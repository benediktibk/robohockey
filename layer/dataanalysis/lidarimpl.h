#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"
#include "common/angle.h"
#include <vector>
#include <utility>

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
	class LidarInternalObject;

	class LidarImpl :
			public Lidar
	{
	private:
		typedef std::pair<unsigned int, double> DistanceForSensor;

	public:
		LidarImpl(Hardware::Lidar &lidar);
		virtual ~LidarImpl();

		virtual LidarObjects getAllObjects(const Common::RobotPosition &ownPosition) const;
		virtual bool isObstacleInFront(double speed) const;
		virtual void updateSensorData();
		virtual bool isPuckCollectable(double maximumDistance, const Common::Angle &maximumAngle) const;
		virtual bool isPuckCollected() const;
		virtual Common::Angle getMaximumAngleRight() const;
		virtual Common::Angle getMaximumAngleLeft() const;
		virtual bool canBeSeen(const Common::Circle &object, const Common::RobotPosition &ownPosition) const;
		virtual bool canBeSeenPartly(const Common::Circle &object, const Common::RobotPosition &ownPosition) const;

	private:
		std::list<std::pair<int, int> > findStartAndEndOfObjects(
				const std::list<int> &positiveEdges, const std::list<int> &negativeEdges,
				int &viewAreaMinimum, int &viewAreaMaximum) const;
		Common::DiscreteFunction* readInData() const;
		Common::Angle calculateOrientationFromSensorNumber(unsigned int value) const;
		int calculateSensorNumberFromOrientation(const Common::Angle &angle) const;
		double calculateDistanceToObject(
				const Common::Circle &circle, unsigned int sensorNumber, double distanceToCenter,
				const Common::Angle &angleToCenterOfCircle) const;
		double calculateMinimumDistanceToObstacle(const Common::Angle &angle, double speed) const;
		void clearInternalObjects();
		std::list<LidarInternalObject*> getObjectsCloserThan(double distance) const;
		double canBeSeenPercentage(const Common::Circle &object, const Common::RobotPosition &ownPosition) const;

	private:
		static std::list<int> replaceFollowingEdgesWithBiggestMagnitudePosition(const std::list<int> &edges, const Common::DiscreteFunction &edgeFunction);

	private:
		Hardware::Lidar &m_lidar;
		const unsigned int m_minimumSensorNumber;
		const unsigned int m_maximumSensorNumber;
		const double m_edgeTreshold;
		const int m_minimumWidthInSensorNumbers;
		const double m_maximumWidthInMeter;
		const double m_maximumDistance;
		Common::DiscreteFunction *m_lowPassPart;
		Common::DiscreteFunction *m_highPassPart;
		Common::DiscreteFunction *m_rawData;
		std::vector<LidarInternalObject*> m_objects;
		Common::Angle m_maximumAngleRight;
		Common::Angle m_maximumAngleLeft;
	};
}
}
}

#endif
