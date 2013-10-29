#include "layer/dataanalysis/engineimpl.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

EngineImpl::EngineImpl(Hardware::Engine &engine) :
	m_engine(engine)
{ }

void EngineImpl::setSpeed(double /*magnitude*/, double /*rotation*/)
{
}
