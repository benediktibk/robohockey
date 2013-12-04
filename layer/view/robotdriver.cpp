#include "layer/view/robotdriver.h"
#include "layer/view/model.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/watch.h"
#include "common/robotposition.h"
#include <iostream>
#include <iomanip>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

RobotDriver::RobotDriver(Robot &robot, Field &field, Model &model) :
	m_robot(robot),
	m_field(field),
	m_model(model),
	m_watch(new Common::Watch()),
	m_cantReachTargetOld(false),
	m_stuckAtObstacleOld(false)
{ }

RobotDriver::~RobotDriver()
{
	delete m_watch;
	m_watch = 0;
}

void RobotDriver::update()
{
	double timeDifference = m_watch->getTimeAndRestart();
	cout << setprecision(3) << fixed << "loop time: " << timeDifference*1000 << " ms" << endl;
	if (timeDifference > 0.25)
		cout << setprecision(3) << fixed << "loop time is too high!" << endl;

	m_robot.updateSensorData();
	m_field.update();
	const RobotPosition &positionAndOrientation = m_robot.getCurrentPosition();
	vector<Point> targets = m_model.getAllTargetPoints();
	vector<FieldObject> pucks = m_field.getObjectsWithColorOrderdByDistance(
				m_model.getPuckColor(), positionAndOrientation.getPosition());

	if (m_model.getPuckColor() == FieldObjectColorUnknown)
	{
		vector<FieldObject> bluePucks = m_field.getObjectsWithColorOrderdByDistance(
					FieldObjectColorBlue, positionAndOrientation.getPosition());
		vector<FieldObject> yellowPucks = m_field.getObjectsWithColorOrderdByDistance(
					FieldObjectColorYellow, positionAndOrientation.getPosition());

		pucks.insert(pucks.end(), bluePucks.begin(), bluePucks.end());
		pucks.insert(pucks.end(), yellowPucks.begin(), yellowPucks.end());
	}

	Point closestPuckPosition;
	bool closestPuckValid = pucks.size() > 0;

	if (closestPuckValid)
	{
		const FieldObject &firstPuck = pucks.front();
		closestPuckPosition = firstPuck.getCircle().getCenter();
	}

	if (cantReachTargetOrStuckAtObstacleNewTillLastCall())
	{
		targets.clear();
		m_model.setTargetPoints(targets);
	}
	else if(m_model.getStop())
	{
		m_robot.stop();
		targets.clear();
		m_model.setTargetPoints(targets);
		m_model.setStop(false);
	}
	else if (targets.size() > 0)
	{
		if (m_robot.reachedTarget() || m_robot.stuckAtObstacle() || m_robot.cantReachTarget())
		{
			vector<Point> targetsWithoutFirstOne(targets.begin() + 1, targets.end());
			m_model.setTargetPoints(targetsWithoutFirstOne);
			m_robot.goTo(targets.front());
		}
	}
	else
	{
		if(m_model.getTurnAround())
		{
			m_robot.turnAround();
			m_model.setTurnAround(false);
		}

		if(m_model.getTurnTo())
		{
			Point turnToPoint;
			turnToPoint = m_model.getTurnPoint();
			m_robot.turnTo(turnToPoint);
			m_model.setTurnTo(false);
		}

		if(m_model.getCollectPuckInFront())
		{
			if (closestPuckValid)
				m_robot.collectPuckInFront(closestPuckPosition);

			m_model.setCollectPuckInFront(false);
		}
		else if (m_robot.isCollectingPuck() && closestPuckValid)
			m_robot.updatePuckPosition(closestPuckPosition);

		if(m_model.getLeavePuckInFront())
		{
			m_robot.leaveCollectedPuck();
			m_model.setLeavePuckInFront(false);
		}

		if(m_model.getCalibratePosition())
		{
			m_field.calibratePosition();
			m_model.setCalibratePosition(false);
		}
	}

	m_model.setData(
				m_field.getAllFieldObjects(), m_robot.stuckAtObstacle(),
				m_robot.reachedTarget(), m_robot.getCurrentPosition(),
				m_robot.getCurrentTarget(), m_robot.isMoving(), m_robot.cantReachTarget(),
				m_robot.isPuckCollected(), m_robot.isPuckCollectable(), closestPuckValid,
				closestPuckPosition, m_robot.isRotating());

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
