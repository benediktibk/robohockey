#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"

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

void RobotImpl::goTo(const RoboHockey::Common::Point &/*position*/)
{

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
