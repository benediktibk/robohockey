#include "layer/view/model.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

Model::Model() :
	m_stuckAtObstacle(false),
	m_reachedTarget(false),
	m_isMoving(false)
{ }

void Model::setData(
		const vector<FieldObject> &fieldObjects,
		bool stuckAtObstacle, bool reachedTarget,
		const RobotPosition &currentPosition, const Point &currentTarget,
		bool isMoving)
{
	m_fieldObjects = fieldObjects;
	m_stuckAtObstacle = stuckAtObstacle;
	m_reachedTarget = reachedTarget;
	m_currentPosition = currentPosition;
	m_currentTarget = currentTarget;
	m_isMoving = isMoving;

	emit robotDataChanged();
}

void Model::setData(const vector<Point> &targetPositions)
{
	m_targetPositions = targetPositions;

	emit targetPositionsChanged();
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

const RobotPosition &Model::getCurrentPosition() const
{
	return m_currentPosition;
}

const Point Model::getCurrentTarget() const
{
	return m_currentTarget;
}
