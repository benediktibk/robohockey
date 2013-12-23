#include "layer/autonomous/fieldmock.h"
#include "common/robotposition.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock() :
	m_achievedGoals(0),
	m_negativeCoordinatesOutside(false),
	m_hiddenPucks(0),
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

unsigned int FieldMock::getNumberOfObjectsWithColor(FieldColor) const
{
	return m_objects.size();
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

void FieldMock::setCalibrationReturnPosition(RobotPosition newOrigin)
{
	m_newOrigin = newOrigin;
}

void FieldMock::setTrueTeamColor(FieldColor teamColor)
{
	m_teamColor = teamColor;
}

RobotPosition FieldMock::getNewOriginFromFieldDetection()
{
	return m_newOrigin;
}

void FieldMock::transformFieldToNewOrigin(const RobotPosition /*newOrigin*/)
{
	m_calibrated = true;
}

std::vector<RobotPosition> FieldMock::getTargetsForWaitingPhase() const
{
	std::vector<RobotPosition> targets;
	targets.push_back(RobotPosition());
	targets.push_back(RobotPosition());
	targets.push_back(RobotPosition());

	return targets;
}

bool FieldMock::isCalibrated() const
{
	return m_calibrated;
}

FieldColor FieldMock::getOwnTeamColor() const
{
    return m_teamColor;
}

FieldColor FieldMock::getEnemyTeamColor() const
{
    if (m_teamColor == FieldColorYellow)
        return FieldColorBlue;
    else
        return FieldColorYellow;
}

void FieldMock::detectTeamColorWithGoalInFront()
{ }

unsigned int FieldMock::getNumberOfHiddenPucks()
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

std::list<RobotPosition> FieldMock::getTargetsForCollectingOnePuck(FieldColor) const
{
	return list<RobotPosition>();
}

unsigned int FieldMock::getNumberOfAchievedGoals()
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
