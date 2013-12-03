#include "layer/view/model.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;

Model::Model() :
	m_stuckAtObstacle(false),
	m_reachedTarget(false),
	m_isMoving(false),
	m_turnAround(false),
	m_stop(false),
	m_turn(false),
	m_collectPuck(false),
	m_calibratePosition(false),
	m_leavePuck(false),
	m_cantReachTarget(false),
	m_isPuckCollected(false),
	m_isPuckCollectable(false),
	m_closestPuckValid(false),
	m_puckColor(FieldObjectColorBlue)
{}

void Model::setData(const vector<FieldObject> &fieldObjects,
		bool stuckAtObstacle, bool reachedTarget,
		const RobotPosition &currentPosition, const Point &currentTarget,
		bool isMoving, bool cantReachTarget, bool isPuckCollected, bool isPuckCollectable,
		bool closestPuckPositionValid, const Point &closestPuckPosition)
{
	m_fieldObjects = fieldObjects;
	m_stuckAtObstacle = stuckAtObstacle;
	m_reachedTarget = reachedTarget;
	m_currentPosition = currentPosition;
	m_currentTarget = currentTarget;
	m_isMoving = isMoving;
	m_cantReachTarget = cantReachTarget;
	m_isPuckCollected = isPuckCollected;
	m_isPuckCollectable = isPuckCollectable;
	m_closestPuckValid = closestPuckPositionValid;
	m_closestPuckPosition = closestPuckPosition;

	emit robotDataChanged();
}

const vector<FieldObject> &Model::getAllFieldObjects() const
{
	return m_fieldObjects;
}

const vector<Point> &Model::getAllTargetPoints() const
{
	return m_targetPositions;
}

void Model::setTargetPoints(const vector<Point> &targets)
{
	m_targetPositions = targets;
	emit dataForViewChanged();
}

bool Model::stuckAtObstacle() const
{
	return m_stuckAtObstacle;
}

bool Model::reachedTarget() const
{
	return m_reachedTarget;
}

bool Model::isMoving() const
{
	return m_isMoving;
}

void Model::setTurnAround(bool value)
{
	m_turnAround = value;
}

void Model::turnToPoint(double turnToX, double turnToY)
{
	m_turnToPosition.setX(turnToX);
	m_turnToPosition.setY(turnToY);
}

void Model::setTurnTo(bool value)
{
	m_turn = value;
}

void Model::setStop(bool value)
{
	m_stop = value;
}

bool Model::getStop()
{
	return m_stop;
}

bool Model::getTurnTo()
{
	return m_turn;
}

Point Model::getTurnPoint()
{
	return m_turnToPosition;
}

void Model::setCollectPuckInFront(bool value)
{
	m_collectPuck = value;
}

bool Model::getCollectPuckInFront()
{
	return m_collectPuck;
}

void Model::setCalibratePosition(bool value)
{
	m_calibratePosition = value;
}

bool Model::getCalibratePosition()
{
	return m_calibratePosition;
}

void Model::setLeavePuckInFront(bool value)
{
	m_leavePuck = value;
}

bool Model::getLeavePuckInFront()
{
	return m_leavePuck;
}

bool Model::cantReachTarget() const
{
	return m_cantReachTarget;
}

bool Model::isPuckCollected() const
{
	return m_isPuckCollected;
}

bool Model::isPuckCollectable() const
{
	return m_isPuckCollectable;
}

bool Model::isClosestPuckValid() const
{
	return m_closestPuckValid;
}

const Point &Model::getClosestPuckPosition() const
{
	assert(isClosestPuckValid());
	return m_closestPuckPosition;
}

FieldObjectColor Model::getPuckColor() const
{
	return m_puckColor;
}

void Model::setPuckColor(FieldObjectColor color)
{
	m_puckColor = color;
}

bool Model::getTurnAround()
{
	return m_turnAround;
}

const RobotPosition &Model::getCurrentPosition() const
{
	return m_currentPosition;
}

const Point Model::getCurrentTarget() const
{
	return m_currentTarget;
}
