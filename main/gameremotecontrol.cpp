#include "main/gameremotecontrol.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "layer/view/model.h"
#include "layer/view/controller.h"
#include <QtGui/QApplication>
#include <iostream>
#include "layer/autonomous/route.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Main;

GameRemoteControl::GameRemoteControl(int argc, char **argv) :
	Game(argc, argv),
	m_model(new Model()),
	m_controller(new Controller(*m_model)),
	m_cantReachTargetOld(false),
	m_stuckAtObstacleOld(false)
{
	m_controller->show();

	cout << "starting the remote control" << endl;
}

GameRemoteControl::~GameRemoteControl()
{
	delete m_controller;
	m_controller = 0;
	delete m_model;
	m_model = 0;
}

bool GameRemoteControl::keepRunning() const
{
	return !m_controller->isClosed();
}

void GameRemoteControl::executeRobotControl()
{
	Robot &robot = getRobot();
	Field &field = getField();
	const RobotPosition &positionAndOrientation = robot.getCurrentPosition();
	vector<Point> targets = m_model->getAllTargetPoints();
	vector<FieldObject> pucks = field.getObjectsWithColorOrderdByDistance(
				m_model->getPuckColor(), positionAndOrientation.getPosition());

	if (m_model->getPuckColor() == FieldColorUnknown)
	{
		vector<FieldObject> bluePucks = field.getObjectsWithColorOrderdByDistance(
					FieldColorBlue, positionAndOrientation.getPosition());
		vector<FieldObject> yellowPucks = field.getObjectsWithColorOrderdByDistance(
					FieldColorYellow, positionAndOrientation.getPosition());

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
		m_model->setTargetPoints(targets);
	}
	else if(m_model->getStop())
	{
		robot.stop();
		targets.clear();
		m_model->setTargetPoints(targets);
		m_model->setStop(false);
	}
	else if (targets.size() > 0)
	{
		if (robot.reachedTarget() || robot.stuckAtObstacle() || robot.cantReachTarget())
		{
			vector<Point> targetsWithoutFirstOne(targets.begin() + 1, targets.end());
			m_model->setTargetPoints(targetsWithoutFirstOne);
			robot.goTo(RobotPosition(targets.front(), 0));
		}
	}
	else
	{
		if(m_model->getTurnAround())
		{
			robot.turnAround();
			m_model->setTurnAround(false);
		}

		if(m_model->getTurnTo())
		{
			Point turnToPoint;
			turnToPoint = m_model->getTurnPoint();
			robot.turnTo(turnToPoint);
			m_model->setTurnTo(false);
		}

		if(m_model->getCollectPuckInFront())
		{
			if (closestPuckValid)
				robot.collectPuckInFront(closestPuckPosition);

			m_model->setCollectPuckInFront(false);
		}
		else if (robot.isCollectingPuck() && closestPuckValid)
			robot.updatePuckPosition(closestPuckPosition);

		if(m_model->getLeavePuckInFront())
		{
			robot.leaveCollectedPuck();
			m_model->setLeavePuckInFront(false);
		}

		if(m_model->getCalibratePosition())
		{
			field.calibratePosition();
			m_model->setCalibratePosition(false);
		}
	}
	m_model->setData(
				field.getAllFieldObjects(), robot.getAllRoutePoints(), robot.stuckAtObstacle(),
				robot.reachedTarget(), robot.getCurrentPosition(),
				robot.getCurrentTarget(), robot.isMoving(), robot.cantReachTarget(),
				robot.isPuckCollected(), robot.isPuckCollectable(), closestPuckValid,
				closestPuckPosition, robot.isRotating());
}


bool GameRemoteControl::cantReachTargetOrStuckAtObstacleNewTillLastCall()
{
	Robot &robot = getRobot();
	bool cantReachTarget = robot.cantReachTarget();
	bool stuckAtObstacle = robot.stuckAtObstacle();
	bool result = (stuckAtObstacle && !m_stuckAtObstacleOld) || (cantReachTarget && !m_cantReachTargetOld);
	m_cantReachTargetOld = cantReachTarget;
	m_stuckAtObstacleOld = stuckAtObstacle;
	return result;
}

