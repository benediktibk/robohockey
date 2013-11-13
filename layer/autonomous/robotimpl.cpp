#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/odometry.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser) :
	m_dataAnalyser(dataAnalyser)
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
}

void RobotImpl::goTo(const RoboHockey::Common::Point &position)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	//! @todo imlement a router to find a path to the target without tackling obstacles
	engine.goToStraight(position);
	m_targetPosition = position;
}

void RobotImpl::turnTo(const Point &position)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnToTarget(position);
}

bool RobotImpl::stuckAtObstacle()
{
	DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
	return sonar.isObstacleDirectInFront();
}

bool RobotImpl::reachedTarget()
{
	Compare compare(0.1);
	return compare.isFuzzyEqual(m_currentPosition, m_targetPosition);
}

vector<FieldObject> RobotImpl::getAllFieldObjects()
{
	return vector<FieldObject>();
}

void RobotImpl::updateActuators()
{
	m_dataAnalyser->updateActuators();
}

void RobotImpl::updateSensorData()
{
	m_dataAnalyser->updateSensorData();
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	m_currentPosition = odometry.getCurrentPosition();
}

void RobotImpl::stop()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
}

void RobotImpl::collectPuckInFront()
{ }

bool RobotImpl::isMoving()
{
	return false;
}

void RobotImpl::calibratePosition()
{ }

void RobotImpl::turnAround()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnAround();
}

Point RobotImpl::getCurrentPosition()
{
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	return odometry.getCurrentPosition();
}

RobotImpl::RobotImpl(const RobotImpl &)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
