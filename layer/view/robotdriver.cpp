#include "layer/view/robotdriver.h"
#include "layer/view/model.h"
#include "layer/autonomous/robot.h"
#include "common/watch.h"
#include "common/robotposition.h"
#include <iostream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

const double RobotDriver::m_maximumLoopTime = 0.2;

RobotDriver::RobotDriver(Robot &robot, Model &model) :
	m_robot(robot),
	m_model(model),
	m_watch(new Watch()),
	m_lastTime(0)
{
	m_lastTime = m_watch->getTime();
}

RobotDriver::~RobotDriver()
{
	delete m_watch;
	m_watch = 0;
}

void RobotDriver::update()
{
	double currentTime = m_watch->getTime();
	double timeDifference = currentTime - m_lastTime;
	m_lastTime = currentTime;

	if (timeDifference > m_maximumLoopTime)
		cout << "loop time is too big: " << timeDifference*1000 << " ms" << endl;

	m_robot.updateSensorData();
	vector<Point> targets = m_model.getAllTargetPoints();

	if(m_model.getTurnAround() && targets.size() == 0 && m_robot.reachedTarget())
	{
		m_robot.turnAround();
		m_model.setData(targets,false);
	}

	if (m_robot.reachedTarget() && targets.size() > 0 && !m_model.getTurnAround())
	{
		vector<Point> targetsWithoutFirstOne(targets.begin() + 1, targets.end());
		m_model.setData(targetsWithoutFirstOne, false);
		m_robot.goTo(targets.front());
	}

	m_model.setData(
				m_robot.getAllFieldObjects(), m_robot.stuckAtObstacle(),
				m_robot.reachedTarget(), m_robot.getCurrentPosition(),
				m_robot.getCurrentTarget(), m_robot.isMoving());

	m_robot.updateActuators();

	if (m_robot.stuckAtObstacle())
	{
		cout << "stuck at obstacle" << endl;
		m_model.setData(vector<Point>(), false);
	}
}
