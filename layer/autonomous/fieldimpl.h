#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "layer/autonomous/field.h"
#include "common/fieldcolor.h"
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
		virtual const std::vector<Common::Circle>& getAllSoftObstacles() const;
		virtual const std::vector<Common::Circle>& getAllHardObstacles() const;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldColor color, const Common::Point &position) const;
		virtual bool calibratePosition();
		unsigned int achievedGoals();
		unsigned int enemyHiddenPucks();
		virtual bool isPointInsideField(const Common::Point &point) const;
		virtual bool numberOfPucksChanged() const;
		virtual bool isCalibrated() const;
		virtual Common::FieldColor getOwnTeamColor() const;
		virtual void detectTeamColorWithGoalInFront();
		virtual std::list<Common::RobotPosition> getTargetsForGoalDetection() const;
		virtual std::list<Common::RobotPosition> getTargetsForScoringGoals() const;
		virtual std::list<Common::RobotPosition> getTargetsForFinalPosition() const;
		virtual std::list<Common::RobotPosition> getTargetsForSearchingPucks() const;
		virtual std::list<Common::RobotPosition> getTargetsForHidingEnemyPucks() const;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuck() const;
		virtual void setTrueTeamColor(Common::FieldColor trueTeamColor);
		virtual Common::RobotPosition getNewOriginOfFieldDetection();
		virtual void transformFieldToNewOrigin(const Common::RobotPosition newOrigin);

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

		std::vector<Common::Point> *getPointsOfObjectsWithDiameterAndColor(double diameter, Common::FieldColor color);
		std::vector<FieldObject> getObjectsWithColor(Common::FieldColor color) const;

		virtual std::vector<FieldObject> moveAllFieldObjectsInVisibleAreaToTemporaryVector();
		bool isPointFuzzyInsideField(const Common::Point &point, double epsilon) const;
		void removeAllFieldObjectsOutsideOfField();

	private:
		DataAnalysis::Odometry *m_odometry;
		const DataAnalysis::Lidar *m_lidar;
		DataAnalysis::Camera *m_camera;
		const Robot *m_robot;

		Common::RobotPosition *m_position;
		std::vector<FieldObject> m_fieldObjects;
		std::vector<Common::Circle> m_softObstacles;
		std::vector<Common::Circle> m_hardObstacles;
		FieldState m_fieldState;
		bool m_numberOfPucksChanged;
		unsigned int m_achievedGoals;
		unsigned int m_hiddenPucks;
		Common::FieldColor m_teamColor;
	};
}
}
}

#endif
