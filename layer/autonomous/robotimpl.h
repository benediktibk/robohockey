#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"
#include "common/point.h"

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
	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser);
		virtual ~RobotImpl();

		virtual void goTo(const Common::Point &position);
		virtual bool stuckAtObstacle();
		virtual bool reachedTarget();
		virtual std::vector<FieldObject> getAllFieldObjects();
		virtual void updateActuators();
		virtual void updateSensorData();
		virtual void stop();

	private:
		// forbid copies
		RobotImpl(const RobotImpl &robot);
		void operator=(const RobotImpl &robot);

	private:
		DataAnalysis::DataAnalyser *m_dataAnalyser;
		Common::Point m_currentPosition;
		Common::Point m_targetPosition;
	};
}
}
}

#endif
