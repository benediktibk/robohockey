#include "layer/strategy/fielddetectionstatemachine/initialstatetest.h"
#include "layer/strategy/fielddetectionstatemachine/initialstate.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::nextState_always_detectFieldState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	InitialState initialState(robot, field, referee, logger);

	State *state = initialState.nextState();

	DetectField *stateCasted = dynamic_cast<DetectField*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}



