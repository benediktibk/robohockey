#include "layer/autonomous/robotmock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

RobotMock::RobotMock() :
	m_stuckAtObstacle(false),
	m_reachedTarget(false),
	m_callsToUpdateActuators(0),
	m_callsToUpdateSensorData(0)
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

vector<FieldObject> RobotMock::getAllFieldObjects()
{
	return m_fieldObjects;
}

void RobotMock::updateActuators()
{
	++m_callsToUpdateActuators;
}

void RobotMock::updateSensorData()
{
	++m_callsToUpdateSensorData;
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

void RobotMock::setFieldObjects(const vector<FieldObject> &objects)
{
	m_fieldObjects = objects;
}

const Point &RobotMock::getLastTarget() const
{
	return m_lastTarget;
}
