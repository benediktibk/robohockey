#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H

#include "layer/autonomous/field.h"

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
		virtual std::vector<FieldObject> getObjectsWithColorOrderdByDistance(Common::FieldObjectColor color, const Common::Point &position) const;
		virtual unsigned int achievedGoals();
		virtual void setAchievedGoals(unsigned int goalsAchieved);
		virtual void setEnemyHiddenPucks(unsigned int enemyHiddenPucks);
		virtual bool calibratePosition();
		virtual bool isPointInsideField(const Common::Point &point) const;
		virtual unsigned int enemyHiddenPucks();
		virtual bool numberOfPucksChanged() const;
		virtual Common::RobotPosition getTargetPositionForGoalDetection() const;

		void setFieldObjects(const std::vector<FieldObject> &objects);
		void setSoftObstacles(const std::vector<Common::Circle> &obstacles);
		void setNegativeCoordinatesOutside(bool value);
		void setCalibrationReturn(bool value);

	private:
		std::vector<FieldObject> m_objects;
		std::vector<Common::Circle> m_softObstacles;
		std::vector<Common::Circle> m_hardObstacles;
		unsigned int m_achievedGoals;
		bool m_negativeCoordinatesOutside;
		unsigned int m_hiddenPucks;
		bool m_calibrated;
	};
}
}
}

#endif
