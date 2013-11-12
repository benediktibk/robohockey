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
	class LidarImpl;
	class SonarImpl;
	class OdometryImpl;
	class CameraImpl;
}

namespace Autonomous
{
	class FieldObject;

	class FieldImpl :
			public Field
	{
	public:
		FieldImpl(DataAnalysis::OdometryImpl &odometry, DataAnalysis::LidarImpl &lidar, DataAnalysis::CameraImpl &camera);
		virtual ~FieldImpl();

		virtual void update();
		virtual std::vector<FieldObject> &getAllFieldObjects();

	private:
		virtual void updateWithLidarData();
		virtual void updateWithOdometryData();
		virtual void updateWithCameraData();

		void transformCoordinateSystem(Common::Point &newOrigin, double rotation);
		void rotateCoordinateSystem(double alpha);
		void moveCoordinateSystem(Common::Point &newOrigin);

		std::vector<Common::Point> &getPointsOfObjectsWithDiameterAndColor(double diameter, FieldObjectColor color);

		virtual void removeAllFieldObjectsInVisibleArea();
		bool isTargetPointRightOfLineWithParameters(Common::Point &referencePoint, Common::Point &directionVector, Common::Point &target);



	private:
		DataAnalysis::OdometryImpl *m_odometry;
		DataAnalysis::LidarImpl *m_lidar;
		DataAnalysis::CameraImpl *m_camera;

		Common::RobotPosition *m_position;
		std::vector<FieldObject> m_fieldObjects;
	};
}
}
}

#endif