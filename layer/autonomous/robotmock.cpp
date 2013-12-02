#include "layer/autonomous/robotmock.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

RobotMock::RobotMock() :
	m_stuckAtObstacle(false),
	m_reachedTarget(false),
	m_callsToUpdateActuators(0),
	m_callsToUpdateSensorData(0),
	m_callsToStop(0)
{ }

void RobotMock::goTo(const Point &position)
{
	m_lastTarget = position;
}

bool RobotMock::stuckAtObstacle()
{
	return m_stuckAtObstacle;
}

bool RobotMock::reachedTarget()
{
	return m_reachedTarget;
}

void RobotMock::updateActuators(const Field &)
{
	++m_callsToUpdateActuators;
}

void RobotMock::updateSensorData()
{
	++m_callsToUpdateSensorData;
}

void RobotMock::stop()
{
	++m_callsToStop;
}

unsigned int RobotMock::getCallsToUpdateActuators() const
{
	return m_callsToUpdateActuators;
}

unsigned int RobotMock::getCallsToUpdateSensorData() const
{
	return m_callsToUpdateSensorData;
}

void RobotMock::setStuckAtObstacle(bool value)
{
	m_stuckAtObstacle = value;
}

void RobotMock::setReachedTarget(bool value)
{
	m_reachedTarget = value;
}

const Point &RobotMock::getLastTarget() const
{
	return m_lastTarget;
}

unsigned int RobotMock::getCallsToStop() const
{
	return m_callsToStop;
}

void RobotMock::collectPuckInFront(const Point &)
{ }

void RobotMock::leaveCollectedPuck()
{ }

bool RobotMock::isMoving()
{
	return false;
}

void RobotMock::turnAround()
{ }

void RobotMock::turnTo(const Point &)
{ }

RobotPosition RobotMock::getCurrentPosition() const
{
	return RobotPosition();
}

Point RobotMock::getCurrentTarget() const
{
	return Point();
}

bool RobotMock::cantReachTarget() const
{
	return false;
}

bool RobotMock::isPuckCollected() const
{
	return false;
}

bool RobotMock::isPuckCollectable() const
{
	return false;
}
