#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTMOCK_H

#include "layer/autonomous/robot.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyser;
}

namespace Autonomous
{
	class RobotMock :
			public Robot
	{
	public:
		RobotMock();

		virtual void goTo(const Common::Point &position);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual std::vector<FieldObject> getAllFieldObjects();
		virtual void updateActuators();
		virtual void updateSensorData();
		virtual void stop();
		unsigned int getCallsToUpdateActuators() const;
		unsigned int getCallsToUpdateSensorData() const;
		void setStuckAtObstacle(bool value);
		void setReachedTarget(bool value);
		void setFieldObjects(const std::vector<FieldObject> &objects);
		const Common::Point& getLastTarget() const;
		unsigned int getCallsToStop() const;
		virtual void collectPuckInFront();
		virtual bool isMoving();
		virtual void calibratePosition();
		virtual void turnAround();

	private:
		Common::Point m_lastTarget;
		bool m_stuckAtObstacle;
		bool m_reachedTarget;
		std::vector<FieldObject> m_fieldObjects;
		unsigned int m_callsToUpdateActuators;
		unsigned int m_callsToUpdateSensorData;
		unsigned int m_callsToStop;
	};
}
}
}

#endif
