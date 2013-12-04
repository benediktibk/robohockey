#ifndef ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVER_H
#define ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVER_H

namespace RoboHockey
{
namespace Common
{
	class Watch;
}

namespace Layer
{
namespace Autonomous
{
	class Robot;
	class Field;
}

namespace View
{
	class Model;

	class RobotDriver
	{
	public:
		RobotDriver(Autonomous::Robot &robot, Autonomous::Field &field, Model &model);
		~RobotDriver();

		void update();

	private:
		bool cantReachTargetOrStuckAtObstacleNewTillLastCall();
		bool reachedTargetNewTillLastCall();

	private:
		Autonomous::Robot &m_robot;
		Autonomous::Field &m_field;
		Model &m_model;
		double m_lastTime;
		static const double m_maximumLoopTime;
		bool m_cantReachTargetOld;
		bool m_stuckAtObstacleOld;
	};
}
}
}

#endif
