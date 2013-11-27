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

	class FieldImpl :
			public Field
	{
	public:
		FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera);
		virtual ~FieldImpl();

		virtual void update();
		virtual std::vector<FieldObject> &getAllFieldObjects();

		virtual bool calibratePosition();

	private:
		virtual void updateWithLidarData();
		virtual void updateWithOdometryData();
		virtual void updateWithCameraData();

		FieldObject& getNextObjectFromPosition(Common::Point position);
		std::vector<FieldObject>::iterator getNextObjectFromPosition(std::vector<FieldObject> &fieldObjects, Common::Point position);
		bool tryToMergeLidarAndFieldObject(FieldObject &fieldObject, const DataAnalysis::LidarObject &lidarObject);

		void transformCoordinateSystem(Common::Point &newOrigin, double rotation);
		void moveCoordinateSystem(Common::Point &newOrigin);
		void rotateCoordinateSystem(double alpha);

		std::vector<Common::Point> &getPointsOfObjectsWithDiameterAndColor(double diameter, Common::FieldObjectColor color);

		virtual std::vector<FieldObject> moveAllFieldObjectsInVisibleAreaToTemporaryVector();

	private:
		DataAnalysis::Odometry *m_odometry;
		const DataAnalysis::Lidar *m_lidar;
		DataAnalysis::Camera *m_camera;

		Common::RobotPosition *m_position;
		std::vector<FieldObject> m_fieldObjects;
	};
}
}
}

#endif
