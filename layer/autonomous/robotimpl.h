#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"
#include "common/point.h"
#include "common/robotposition.h"

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
	class Field;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser);
		virtual ~RobotImpl();

		virtual void goTo(const Common::Point &position);
		virtual void turnTo(const Common::Point &position);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual std::vector<FieldObject> getAllFieldObjects();
		virtual void updateActuators();
		virtual void updateSensorData();
		virtual void stop();
		virtual void collectPuckInFront();
		virtual bool isMoving();
		virtual void calibratePosition();
		virtual void turnAround();
		virtual Common::RobotPosition getCurrentPosition();

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

	private:
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Field *m_field;
	};
}
}
}

#endif
