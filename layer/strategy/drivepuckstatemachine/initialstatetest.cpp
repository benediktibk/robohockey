#include "layer/strategy/drivepuckstatemachine/initialstatetest.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/drivepucktoachivegoals.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::nextState_always_findPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuck *drivePuck = new DrivePuckToAchiveGoals();
	InitialState initialState(robot, field, referee, drivePuck);
	State *state;
	state = initialState.nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

