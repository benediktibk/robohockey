#include "layer/strategy/fielddetectionstatemachine/calibrationfinishedtest.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;


void CalibrationFinishedTest::nextState_always_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CalibrationFinished calibrationFinishedState(robot, field, referee);

	calibrationFinishedState.update();

	State *state;
	state = calibrationFinishedState.nextState();
	CPPUNIT_ASSERT(state == 0);

}
