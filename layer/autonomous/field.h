#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H

#include <vector>
#include <list>
#include "common/fieldobjectcolor.h"
#include "layer/autonomous/fieldobject.h"

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
	class Field
	{
	public:
		virtual ~Field() { }

		virtual void update() = 0;
		virtual unsigned int achievedGoals() = 0;
		virtual const std::vector<FieldObject>& getAllFieldObjects() const = 0;
		virtual const std::vector<Common::Circle>& getAllSoftObstacles() const = 0;
		virtual const std::vector<Common::Circle>& getAllHardObstacles() const = 0;
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldObjectColor color, const Common::Point &position) const = 0;

		virtual bool calibratePosition() = 0;
		virtual bool isPointInsideField(const Common::Point &point) const = 0;
		virtual unsigned int enemyHiddenPucks() = 0;
		virtual bool numberOfPucksChanged() const = 0;
		virtual bool isCalibrated() const = 0;
		virtual Common::FieldObjectColor getOwnTeamColor() const = 0;

		virtual std::list<Common::RobotPosition> getTargetsForGoalDetection() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForScoringGoals() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForFinalPosition() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForSearchingPucks() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForHidingEnemyPucks() const = 0;
		virtual std::list<Common::RobotPosition> getTargetsForCollectingOnePuck() const = 0;
	};
}
}
}

#endif
