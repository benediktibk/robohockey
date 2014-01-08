#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H

#include <vector>
#include <list>
#include "common/fieldcolor.h"
#include "layer/autonomous/fieldobject.h"
#include "layer/autonomous/fieldpositionchecker.h"

namespace RoboHockey
{
namespace Common
{
	class Point;
	class RobotPosition;
}
namespace Layer
{
namespace Autonomous
{
	class Field :
			public FieldPositionChecker
	{
	public:
		virtual ~Field() { }

		virtual void update() = 0;
		virtual unsigned int getNumberOfAchievedGoals() const = 0;
		virtual const std::vector<FieldObject>& getAllFieldObjects() const = 0;
		virtual const std::vector<Common::Circle>& getAllSoftObstacles() const = 0;
		virtual const std::vector<Common::Circle>& getAllHardObstacles() const = 0;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldColor color, const Common::Point &position) const = 0;
		virtual unsigned int getNumberOfObjectsWithColor(Common::FieldColor color) const = 0;

		virtual bool calibratePosition() = 0;
		virtual unsigned int getNumberOfHiddenPucks() const = 0;
		virtual bool isCalibrated() const = 0;
		virtual Common::FieldColor getOwnTeamColor() const = 0;
		virtual Common::FieldColor getEnemyTeamColor() const = 0;
		virtual void detectTeamColorWithGoalInFront() = 0;
		virtual void setTrueTeamColor(Common::FieldColor trueTeamColor) = 0;
		virtual Common::RobotPosition getNewOriginFromFieldDetection(unsigned int &outNumberOfBorderstones) = 0;
		virtual void transformFieldToNewOrigin(const Common::RobotPosition newOrigin) = 0;

		virtual std::list<Common::RobotPosition> getTargetsForGoalDetection() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForScoringGoals() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForFinalPosition() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForSearchingPucks() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForHidingEnemyPucks() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuck(Common::FieldColor puckColor) const = 0;
		virtual std::vector<Common::RobotPosition> getTargetsForWaitingPhase() const = 0;
	};
}
}
}

#endif
