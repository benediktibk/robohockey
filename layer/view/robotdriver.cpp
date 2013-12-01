#include "layer/view/robotdriver.h"
#include "layer/view/model.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/watch.h"
#include "common/robotposition.h"
#include <iostream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

const double RobotDriver::m_maximumLoopTime = 0.2;

RobotDriver::RobotDriver(Robot &robot, Field &field, Model &model) :
	m_robot(robot),
	m_field(field),
	m_model(model),
	m_watch(new Watch()),
	m_lastTime(0),
	m_cantReachTargetOld(false),
	m_stuckAtObstacleOld(false)
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
	m_field.update();
	vector<Point> targets = m_model.getAllTargetPoints();

	if (cantReachTargetOrStuckAtObstacleNewTillLastCall())
	{
		targets.clear();
		m_model.setData(targets, false, false, false, false, false, false);
	}
	else if(m_model.getStop())
	{
		targets.clear();
		m_robot.stop();
		m_model.setData(targets, false, false, false, false, false, false);
	}
	else if (targets.size() > 0)
	{
		if (m_robot.reachedTarget() || m_robot.stuckAtObstacle() || m_robot.cantReachTarget())
		{
			vector<Point> targetsWithoutFirstOne(targets.begin() + 1, targets.end());
			m_model.setData(targetsWithoutFirstOne, false, false, false, false, false, false);
			m_robot.goTo(targets.front());
		}
	}
	else
	{
		if(m_model.getTurnAround() && targets.size() == 0)
		{
			m_robot.turnAround();
			m_model.setData(targets, false, false, false, false, false, false);
		}

		if(m_model.getTurnTo() && targets.size() == 0)
		{
			Point turnToPoint;
			turnToPoint = m_model.getTurnPoint();
			m_robot.turnTo(turnToPoint);
			m_model.setData(targets, false, false, false, false, false, false);
		}

		if(m_model.getCollectPuckInFront() && targets.size() == 0)
		{
			m_robot.collectPuckInFront();
			m_model.setData(targets, false, false, false, false, false, false);
		}

		if(m_model.getLeavePuckInFront() && targets.size() == 0)
		{
			m_robot.leaveCollectedPuck();
			m_model.setData(targets, false, false, false, false, false, false);
		}

		if(m_model.getCalibratePosition() && targets.size() == 0)
		{
			m_field.calibratePosition();
			m_model.setData(targets, false, false, false, false, false, false);
		}
	}

	m_model.setData(
				m_field.getAllFieldObjects(), m_robot.stuckAtObstacle(),
				m_robot.reachedTarget(), m_robot.getCurrentPosition(),
				m_robot.getCurrentTarget(), m_robot.isMoving(), m_robot.cantReachTarget(),
				m_robot.isPuckCollected(), m_robot.isPuckCollectable());

	m_robot.updateActuators(m_field);
}

bool RobotDriver::cantReachTargetOrStuckAtObstacleNewTillLastCall()
{
	bool cantReachTarget = m_robot.cantReachTarget();
	bool stuckAtObstacle = m_robot.stuckAtObstacle();
	bool result = (stuckAtObstacle && !m_stuckAtObstacleOld) || (cantReachTarget && !m_cantReachTargetOld);
	m_cantReachTargetOld = cantReachTarget;
	m_stuckAtObstacleOld = stuckAtObstacle;
	return result;
}
