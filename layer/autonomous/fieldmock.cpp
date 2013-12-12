#include "layer/autonomous/fieldmock.h"
#include "common/robotposition.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock() :
	m_negativeCoordinatesOutside(false),
	m_calibrated(false)
{ }

void FieldMock::update()
{ }

const vector<FieldObject>& FieldMock::getAllFieldObjects() const
{
	return m_objects;
}

const vector<Circle>& FieldMock::getAllSoftObstacles() const
{
	return m_softObstacles;
}

const vector<Circle> &FieldMock::getAllHardObstacles() const
{
	return m_hardObstacles;
}

vector<FieldObject> FieldMock::getObjectsWithColorOrderdByDistance(FieldObjectColor, const Point&) const
{
	return vector<FieldObject>();
}

bool FieldMock::calibratePosition()
{
	return m_calibrated;
}

bool FieldMock::isPointInsideField(const Point &point) const
{
	if (m_negativeCoordinatesOutside && (point.getX() < 0 || point.getY() < 0))
		return false;
	else
		return true;
}

void FieldMock::setFieldObjects(const vector<FieldObject> &objects)
{
	m_objects = objects;
}

void FieldMock::setSoftObstacles(const vector<Circle> &obstacles)
{
	m_softObstacles = obstacles;
}

void FieldMock::setNegativeCoordinatesOutside(bool value)
{
	m_negativeCoordinatesOutside = value;
}

void FieldMock::setCalibrationReturn(bool value)
{
	m_calibrated = value;
}

unsigned int FieldMock::enemyHiddenPucks()
{
	return m_hiddenPucks;
}

bool FieldMock::numberOfPucksChanged() const
{
	return false;
}

RobotPosition FieldMock::getTargetPositionForGoalDetection() const
{
	return RobotPosition();
}

unsigned int FieldMock::achievedGoals()
{
	return m_achievedGoals;
}

void FieldMock::setAchievedGoals(unsigned int goalsAchieved)
{
	m_achievedGoals = goalsAchieved;
}

void FieldMock::setEnemyHiddenPucks(unsigned int enemyHiddenPucks)
{
	m_hiddenPucks = enemyHiddenPucks;
}
