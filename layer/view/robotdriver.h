#ifndef ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVER_H
#define ROBOHOCKEY_LAYER_VIEW_ROBOTDRIVER_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Robot;
}

namespace View
{
	class Model;

	class RobotDriver
	{
	public:
		RobotDriver(Autonomous::Robot &robot, Model &model);

		void update();

	private:
		Autonomous::Robot &m_robot;
		Model &m_model;
	};
}
}
}

#endif
