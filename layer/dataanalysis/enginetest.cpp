#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/enginemock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void EngineTest::setSpeed_mockHardwareEngine_atLeastOneCallToSetSpeed()
{
	Hardware::EngineMock hardwareEngine;
	EngineImpl engine(hardwareEngine);

	engine.setSpeed(3, 1);

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}
