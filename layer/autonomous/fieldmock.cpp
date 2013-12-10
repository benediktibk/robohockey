#include "layer/autonomous/fieldmock.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock() :
	m_negativeCoordinatesOutside(false)
{ }

void FieldMock::update()
{ }

const vector<FieldObject>& FieldMock::getAllFieldObjects() const
{
	return m_objects;
}

const vector<Circle>& FieldMock::getAllObstacles() const
{
	return m_obstacles;
}

vector<FieldObject> FieldMock::getObjectsWithColorOrderdByDistance(FieldObjectColor, const Point&) const
{
	return vector<FieldObject>();
}

bool FieldMock::calibratePosition()
{
	return false;
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

void FieldMock::setObstacles(const vector<Circle> &obstacles)
{
	m_obstacles = obstacles;
}

void FieldMock::setNegativeCoordinatesOutside(bool value)
{
	m_negativeCoordinatesOutside = value;
}

unsigned int FieldMock::enemyHiddenPucks()
{
    return m_hiddenPucks;
}

bool FieldMock::numberOfPucksChanged() const
{
	return false;
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
