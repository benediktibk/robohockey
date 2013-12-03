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

void Model::setData(const vector<Point> &targetPositions,
		bool turnAround, bool turnTo, bool stop, bool collectPuck,
		bool calibratePosition, bool leavePuck, FieldObjectColor puckColor)
{
	m_targetPositions = targetPositions;
	m_turnAround = turnAround;
	m_turn = turnTo;
	m_stop = stop;
	m_collectPuck = collectPuck;
	m_calibratePosition = calibratePosition;
	m_leavePuck = leavePuck;
	m_puckColor = puckColor;

	assert(m_puckColor == FieldObjectColorBlue || m_puckColor == FieldObjectColorYellow);
	emit dataForViewChanged();
}

const vector<FieldObject> &Model::getAllFieldObjects() const
{
	return m_fieldObjects;
}

const vector<Point> &Model::getAllTargetPoints() const
{
	return m_targetPositions;
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

bool Model::turnAround()
{
	m_turnAround = true;
	return m_turnAround;
}

void Model::turnToPoint(double turnToX, double turnToY)
{
	m_turnToPosition.setX(turnToX);
	m_turnToPosition.setY(turnToY);
}

bool Model::turnTo()
{
	m_turn = true;
	return m_turn;
}

bool Model::stop()
{
	m_stop = true;
	return m_stop;
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

void Model::collectPuckInFront()
{
	m_collectPuck = true;
}

bool Model::getCollectPuckInFront()
{
	return m_collectPuck;
}

void Model::calibratePosition()
{
	m_calibratePosition = true;
}

bool Model::getCalibratePosition()
{
	return m_calibratePosition;
}

void Model::leavePuckInFront()
{
	m_leavePuck = true;
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
