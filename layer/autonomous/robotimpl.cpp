#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;

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
