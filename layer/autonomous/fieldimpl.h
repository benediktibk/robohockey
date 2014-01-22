#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "common/angle.h"
#include "layer/autonomous/field.h"
#include "common/fieldcolor.h"
#include <vector>
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Point;
	class RobotPosition;
	class Logger;
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
	class CameraObject;
}

namespace Autonomous
{
	class FieldObject;
	class Robot;
	class FieldDetector;

	class FieldImpl :
			public Field
	{
	private:
		enum FieldState { FieldStateUnknownPosition,
						  FieldStateCalibrated
						};

	public:
		FieldImpl(DataAnalysis::Odometry &odometry, const DataAnalysis::Lidar &lidar, DataAnalysis::Camera &camera,
				  Robot &autonomousRobot, Common::Logger &logger);
		virtual ~FieldImpl();

		virtual void update();
		virtual const std::vector<FieldObject>& getAllFieldObjects() const;
		virtual const std::vector<Common::Circle>& getAllSoftObstacles() const;
		virtual const std::vector<Common::Circle>& getAllHardObstacles() const;
		virtual const std::vector<Common::Circle>& getAllHardAndVisibleObstacles() const;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldColor color) const;
		virtual unsigned int getNumberOfObjectsWithColor(Common::FieldColor color) const;
		virtual bool calibratePosition();
		virtual unsigned int getNumberOfAchievedGoals() const;
		virtual unsigned int getNumberOfPuckInEnemyThird() const;
		virtual unsigned int getNumberOfHiddenPucks() const;
		virtual unsigned int getEstimatedNumberOfGoals() const;
		virtual void increaseNumberOfEstimatedGoals();
		virtual bool isPointInsideField(const Common::Point &point) const;
		virtual bool isCalibrated() const;
		virtual Common::FieldColor getOwnTeamColor() const;
		virtual Common::FieldColor getEnemyTeamColor() const;
		virtual void detectTeamColorWithGoalInFront();
		virtual std::list<Common::RobotPosition> getTargetsForGoalDetection() const;
		virtual std::list<Common::RobotPosition> getTargetsForScoringGoals() const;
		virtual std::list<Common::RobotPosition> getTargetsForFinalPosition() const;
		virtual std::list<Common::RobotPosition> getTargetsForSearchingPucks() const;
		virtual std::list<Common::Point> getTargetsForTurningToUnknownObjects() const;
		virtual std::list<Common::RobotPosition> getTargetsForHidingEnemyPucks() const;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuck(Common::FieldColor puckColor) const;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuckNotInEnemyThird(Common::FieldColor puckColor) const;
		virtual std::list<Common::RobotPosition> getTargetsInEnemyThird() const;
		virtual void setTrueTeamColor(Common::FieldColor trueTeamColor);
		virtual Common::RobotPosition getNewOriginFromFieldDetection(unsigned int &outNumberOfBorderstones, bool onlyAcceptConfirmedResults);
		virtual void transformFieldToNewOrigin(const Common::RobotPosition newOrigin);
		virtual std::vector<Common::RobotPosition> getTargetsForWaitingPhase() const;
		virtual bool isPuckOfColorInFront(Common::FieldColor color) const;
		virtual bool isPuckcolorDetected() const;

		double getRangeOfViewArea() const;
		Common::Angle getAngleOfViewArea() const;
		Common::Angle calculateRelativeAngleOfObject(const Common::Circle &circle) const;

	private:
		void updateWithLidarData(double range);
		void tryToMergeDoubledFieldObjects();
		void updateWithOdometryData();
		void updateWithCameraData();
		void removeNotExistingFieldObjects();
		void updateUsefulFieldObjects();
		void updateObstacles();
		void updateAchievedGoals();
		void updateHiddenPucks();
		void updatePucksInEnemyThird();

		std::list<Common::RobotPosition> getTargetsForCollectingOnePuckOrSearchingForColorOfPuck(const Common::Point &position) const;
		std::vector<FieldObject> random(std::vector<FieldObject> &objects);
		std::vector<FieldObject>::iterator getNextObjectFromPosition(Common::Point position);
		std::vector<FieldObject>::iterator getNextObjectFromPosition(std::vector<FieldObject> &fieldObjects, Common::Point position);
		bool tryToMergeLidarAndFieldObject(FieldObject &fieldObject, const DataAnalysis::LidarObject &lidarObject, double epsilon);
		bool couldBeTheSameObject(const Common::Circle &firstObject, const Common::Circle &secondObject, double epsilon) const;
		void tryToMergeLidarAndFieldObjects(
				const std::vector<DataAnalysis::LidarObject> &lidarObjects, std::vector<FieldObject> &visibleFieldObjects,
				std::vector<FieldObject> &newObjects, std::vector<DataAnalysis::LidarObject> &notMergedLidarObjects,
				double epsilon);

		void transformCoordinateSystem(const Common::RobotPosition &newOrigin);
		void moveCoordinateSystem(const Common::Point &newOrigin);
		void rotateCoordinateSystem(const Common::Angle &rotation);

		std::vector<Common::Point> *getPointsOfObjectsWithDiameterAndColor(double diameter, Common::FieldColor color);
		std::vector<FieldObject> getObjectsWithColor(Common::FieldColor color) const;
		std::vector<FieldObject> getObjectsInVisibleSector(Common::Angle angle, double distance) const;

		std::vector<FieldObject> moveAllFieldObjectsInVisibleAreaToTemporaryVector(double range);
		bool isInViewArea(const FieldObject &object, double range) const;
		bool canBeSeen(const FieldObject &object) const;
		bool canBeSeenPartly(const FieldObject &object) const;
		std::vector<FieldObject> getAllPartlyVisibleObjects() const;
		void updateAllNotVisibleObjects();
		bool isPointFuzzyInsideField(const Common::Point &point, double epsilon) const;
		void removeAllFieldObjectsOutsideOfField();
		std::list<DataAnalysis::CameraObject>::iterator getClosestCameraObject(const FieldObject &fieldObject, std::list<DataAnalysis::CameraObject> &cameraObjects) const;

	private:
		Common::Logger &m_logger;
		const unsigned int m_seenTresholdForFieldObjects;
		DataAnalysis::Odometry &m_odometry;
		const DataAnalysis::Lidar &m_lidar;
		DataAnalysis::Camera &m_camera;
		const Robot &m_robot;
		FieldDetector *m_fieldDetector;

		Common::RobotPosition *m_position;
		std::vector<FieldObject> m_fieldObjects;
		std::vector<FieldObject> m_usefulFieldObjects;
		std::vector<Common::Circle> m_softObstacles;
		std::vector<Common::Circle> m_hardObstacles;
		std::vector<Common::Circle> m_hardAndVisibleObstacles;
		FieldState m_fieldState;
		unsigned int m_achievedGoals;
		unsigned int m_puckInEnemyThird;
		unsigned int m_hiddenPucks;
		Common::FieldColor m_teamColor;
		unsigned int m_estimatedAchievedGoals;
	};
}
}
}

#endif
