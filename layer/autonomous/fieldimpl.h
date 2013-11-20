#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "layer/autonomous/field.h"
#include "layer/autonomous/fieldobjectcolor.h"
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

		virtual void tryToFindField();

	private:
		virtual void updateWithLidarData();
		virtual void updateWithOdometryData();
		virtual void updateWithCameraData();

		FieldObject& getNextObjectFromPosition(Common::Point position);

		void transformCoordinateSystem(Common::Point &newOrigin, double rotation);
		void rotateCoordinateSystem(double alpha);
		void moveCoordinateSystem(Common::Point &newOrigin);

		std::vector<Common::Point> &getPointsOfObjectsWithDiameterAndColor(double diameter, FieldObjectColor color);

		virtual void removeAllFieldObjectsInVisibleArea();

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
