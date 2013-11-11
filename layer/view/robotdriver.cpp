#include "layer/view/robotdriver.h"
#include "layer/view/model.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

RobotDriver::RobotDriver(Robot &robot, Model &model) :
	m_robot(robot),
	m_model(model)
{ }

void RobotDriver::update()
{
	m_robot.updateSensorData();
	vector<Point> targets = m_model.getAllTargetPoints();

	if (m_robot.stuckAtObstacle())
	{
		m_model.setData(vector<Point>());
		m_robot.stop();
	}
	else if (m_robot.reachedTarget() && targets.size() > 0)
	{
		vector<Point> targetsWithoutFirstOne(targets.begin() + 1, targets.end());
		m_model.setData(targetsWithoutFirstOne);
		m_robot.goTo(targets.front());
	}
	else if (m_robot.reachedTarget())
		m_robot.stop();

	m_model.setData(m_robot.getAllFieldObjects(), m_robot.stuckAtObstacle(), m_robot.reachedTarget());

	m_robot.updateActuators();
}
