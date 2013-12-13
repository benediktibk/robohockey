#include "layer/autonomous/fieldmock.h"
#include "common/robotposition.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock() :
	m_negativeCoordinatesOutside(false),
	m_calibrated(false),
	m_teamColor(FieldColorUnknown)
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

vector<FieldObject> FieldMock::getObjectsWithColorOrderdByDistance(FieldColor, const Point&) const
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

void FieldMock::setHardObstacles(const std::vector<Circle> &obstacles)
{
	m_hardObstacles = obstacles;
}

void FieldMock::setNegativeCoordinatesOutside(bool value)
{
	m_negativeCoordinatesOutside = value;
}

void FieldMock::setCalibrationReturn(bool value)
{
	m_calibrated = value;
}

void FieldMock::setTrueTeamColor(FieldColor teamColor)
{
	m_teamColor = teamColor;
}

bool FieldMock::isCalibrated() const
{
	return m_calibrated;
}

FieldColor FieldMock::getOwnTeamColor() const
{
	return m_teamColor;
}

void FieldMock::detectTeamColorWithGoalInFront()
{ }

unsigned int FieldMock::enemyHiddenPucks()
{
	return m_hiddenPucks;
}

bool FieldMock::numberOfPucksChanged() const
{
	return false;
}

std::list<RobotPosition> FieldMock::getTargetsForGoalDetection() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldMock::getTargetsForScoringGoals() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldMock::getTargetsForFinalPosition() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldMock::getTargetsForSearchingPucks() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldMock::getTargetsForHidingEnemyPucks() const
{
	return list<RobotPosition>();
}

std::list<RobotPosition> FieldMock::getTargetsForCollectingOnePuck() const
{
	return list<RobotPosition>();
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
