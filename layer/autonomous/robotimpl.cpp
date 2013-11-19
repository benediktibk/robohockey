#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/odometry.h"
#include "common/compare.h"
#include "layer/autonomous/fieldimpl.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser) :
	m_dataAnalyser(dataAnalyser),
	m_field(new FieldImpl(dataAnalyser->getOdometry(), dataAnalyser->getLidar(), dataAnalyser->getCamera()))
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
	delete m_field;
}

void RobotImpl::goTo(const RoboHockey::Common::Point &position)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	//! @todo imlement a router to find a path to the target without tackling obstacles
	engine.goToStraight(position);
}

void RobotImpl::turnTo(const Point &position)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnToTarget(position);
}

bool RobotImpl::stuckAtObstacle()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	return engine.tryingToTackleObstacle();
}

bool RobotImpl::reachedTarget()
{
	//! @todo won't be enough if we try to reach the target in more than one step
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	return engine.reachedTarget();
}

vector<FieldObject> RobotImpl::getAllFieldObjects()
{
	return m_field->getAllFieldObjects();
}

void RobotImpl::updateActuators()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	m_dataAnalyser->updateActuators();

	if (engine.tryingToTackleObstacle())
		engine.stop();
}

void RobotImpl::updateSensorData()
{
	DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	m_dataAnalyser->updateSensorData();
	m_field->update();

	if (sonar.isObstacleDirectInFront())
		engine.lockForwardMovement();
	else
		engine.unlockForwardMovement();
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
	return m_dataAnalyser->getEngine().isMoving();
}

void RobotImpl::calibratePosition()
{ }

void RobotImpl::turnAround()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnAround();
}

RobotPosition RobotImpl::getCurrentPosition()
{
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	return odometry.getCurrentPosition();
}

Point RobotImpl::getCurrentTarget() const
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	return engine.getCurrentTarget();
}

RobotImpl::RobotImpl(const RobotImpl &)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
