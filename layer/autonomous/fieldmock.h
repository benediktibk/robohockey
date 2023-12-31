#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H

#include "layer/autonomous/field.h"
#include "common/robotposition.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{

	class FieldMock :
			public Field
	{
	public:
		FieldMock();

		virtual void update();
		virtual const std::vector<FieldObject>& getAllFieldObjects() const;
		virtual const std::vector<Common::Circle>& getAllSoftObstacles() const;
		virtual const std::vector<Common::Circle>& getAllHardObstacles() const;
		virtual const std::vector<Common::Circle>& getAllHardAndVisibleObstacles() const;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldColor color) const;
		virtual unsigned int getNumberOfObjectsWithColor(Common::FieldColor color) const;
		virtual unsigned int getNumberOfAchievedGoals() const;
		virtual unsigned int getNumberOfPuckInEnemyThird() const;
		virtual bool calibratePosition();
		virtual bool isPointInsideField(const Common::Point &point) const;
		virtual unsigned int getNumberOfHiddenPucks() const;
		virtual unsigned int getEstimatedNumberOfGoals() const;
		virtual void increaseNumberOfEstimatedGoals();
		virtual bool isCalibrated() const;
		virtual Common::FieldColor getOwnTeamColor() const;
		virtual Common::FieldColor getEnemyTeamColor() const;
		virtual void detectTeamColorWithGoalInFront();
		virtual std::list<Common::RobotPosition> getTargetsForGoalDetection() const;
		virtual std::list<Common::RobotPosition> getTargetsForScoringGoals() const;
		virtual std::list<Common::RobotPosition> getTargetsForFinalPosition() const;
		virtual std::list<Common::RobotPosition> getTargetsForSearchingPucks() const;
		virtual std::list<Common::RobotPosition> getTargetsForHidingEnemyPucks() const;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuck(Common::FieldColor puckColor) const;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuckNotInEnemyThird(Common::FieldColor puckColor) const;
		virtual std::list<Common::RobotPosition> getTargetsInEnemyThird() const;
		virtual std::list<Common::Point> getTargetsForTurningToUnknownObjects() const;
		virtual void setTrueTeamColor(Common::FieldColor);
		virtual Common::RobotPosition getNewOriginFromFieldDetection(unsigned int &outNumberOfBorderstones, bool onlyAcceptConfirmedResults);
		virtual void transformFieldToNewOrigin(const Common::RobotPosition newOrigin);
		virtual std::vector<Common::RobotPosition> getTargetsForWaitingPhase() const;
		virtual bool isPuckOfColorInFront(Common::FieldColor color) const;
		virtual bool isPuckcolorDetected() const;

		void setAchievedGoals(unsigned int goalsAchieved);
		void setEnemyHiddenPucks(unsigned int getNumberOfHiddenPucks);
		void setPucksInEnemyThird(unsigned int value);
		void setFieldObjects(const std::vector<FieldObject> &objects);
		void setSoftObstacles(const std::vector<Common::Circle> &obstacles);
		void setHardObstacles(const std::vector<Common::Circle> &obstacles);
		void setHardAndVisibleObstacles(const std::vector<Common::Circle> &obstacles);
		void setNegativeCoordinatesOutside(bool value);
		void setCalibrationReturn(bool value);
		void setIsPuckOfColorInFront(bool value);
		void setIsPuckcolorDetected(bool value);
		void setCalibrationReturnPosition(Common::RobotPosition newOrigin);
		void setObjectsWithColorOrderedByDistance(const std::vector<FieldObject> &objects);
		void setTargetsForTurningToUnknownObjects(const std::list<Common::Point> &targets);

	private:
		std::vector<FieldObject> m_objects;
		std::vector<Common::Circle> m_softObstacles;
		std::vector<Common::Circle> m_hardObstacles;
		std::vector<Common::Circle> m_hardAndVisibleObstacles;
		unsigned int m_achievedGoals;
		unsigned int m_pucksInEnemyThird;
		bool m_negativeCoordinatesOutside;
		unsigned int m_hiddenPucks;
		bool m_calibrated;
		bool m_isPuckOfColorInFront;
		bool m_isPuckcolorDetected;
		Common::FieldColor m_teamColor;
		Common::RobotPosition m_newOrigin;
		std::vector<FieldObject> m_objectsWithColorOrderedByDistance;
		std::list<Common::Point> m_pointsForTurning;
	};
}
}
}

#endif
