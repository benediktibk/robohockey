#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "layer/autonomous/field.h"
#include "common/fieldobjectcolor.h"
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class RobotPosition;
}
namespace Layer
{
namespace DataAnalysis
{
	class Lidar;
	class LidarObject;
	class Sonar;
	class Odometry;
	class Camera;
}

namespace Autonomous
{
	class FieldObject;
	class Robot;

	class FieldImpl :
			public Field
	{
	private:
			enum FieldState { FieldStateUnknownPosition,
							  FieldStateCalibrated
							};

	public:
		FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera, Robot &autonomousRobot);
		virtual ~FieldImpl();

		virtual void update();
		virtual const std::vector<FieldObject>& getAllFieldObjects() const;
		virtual const std::vector<Common::Circle>& getAllObstacles() const;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldObjectColor color, const Common::Point &position) const;
		virtual bool calibratePosition();
		virtual bool isPointInsideField(const Common::Point &point) const;

	private:
		void updateWithLidarData();
		void updateWithOdometryData();
		void updateWithCameraData();
		void updateObstacles();

		FieldObject& getNextObjectFromPosition(Common::Point position);
		std::vector<FieldObject>::iterator getNextObjectFromPosition(std::vector<FieldObject> &fieldObjects, Common::Point position);
		bool tryToMergeLidarAndFieldObject(FieldObject &fieldObject, const DataAnalysis::LidarObject &lidarObject);

		void transformCoordinateSystem(Common::Point &newOrigin, double rotation);
		void moveCoordinateSystem(Common::Point &newOrigin);
		void rotateCoordinateSystem(double alpha);

		std::vector<Common::Point> *getPointsOfObjectsWithDiameterAndColor(double diameter, Common::FieldObjectColor color);
		std::vector<FieldObject> getObjectsWithColor(Common::FieldObjectColor color) const;

		virtual std::vector<FieldObject> moveAllFieldObjectsInVisibleAreaToTemporaryVector();

	private:
		DataAnalysis::Odometry *m_odometry;
		const DataAnalysis::Lidar *m_lidar;
		DataAnalysis::Camera *m_camera;
		const Robot *m_robot;

		Common::RobotPosition *m_position;
		std::vector<FieldObject> m_fieldObjects;
		std::vector<Common::Circle> m_obstacles;
		FieldState m_fieldState;
	};
}
}
}

#endif
