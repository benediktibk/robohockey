#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"

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
}

bool RobotImpl::stuckAtObstacle()
{
	return false;
}

bool RobotImpl::reachedTarget()
{
	return false;
}

vector<FieldObject> RobotImpl::getAllFieldObjects()
{
	return vector<FieldObject>();
}

void RobotImpl::updateActuators()
{
	m_dataAnalyser->updateActuators();
}
