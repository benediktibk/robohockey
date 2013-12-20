#include "layer/strategy/drivepuckstatemachine/initialstatetest.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/drivepuckmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void InitialStateTest::nextState_puckCollected_nextStateIsLeavePuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	robot.setPuckCollected(true);
	InitialState initialState(robot, field, referee, drivePuck);
	State *state;
	state = initialState.nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void InitialStateTest::nextState_numberOfKnownPucksIs0_nextStateIsFindPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	InitialState initialState(robot, field, referee, drivePuck);
	State *state;
	state = initialState.nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void InitialStateTest::nextState_numberOfKnownPucksIs2_nextStateIsDriveToCollectPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	drivePuck->setNumberOfKnownPucksNotInTarget(2);
	InitialState initialState(robot, field, referee, drivePuck);
	State *state;
	state = initialState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

