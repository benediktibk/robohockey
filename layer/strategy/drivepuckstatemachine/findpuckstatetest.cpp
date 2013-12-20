#include "layer/strategy/drivepuckstatemachine/findpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
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

void FindPuckStateTest::nextState_targetReached_nextStateIsDriveToCollectPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	robot.setReachedTarget(true);
	FindPuckState findPuckState(robot, field, referee, drivePuck);
	State *driveToState;
	driveToState = findPuckState.nextState();
	State *state;
	state = driveToState->nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void FindPuckStateTest::nextState_cantReachTarget_nextStateIsFindPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	robot.setCantReachedTarget(true);
	FindPuckState findPuckState(robot, field, referee, drivePuck);
	State *driveToState;
	driveToState = findPuckState.nextState();
	State *state;
	state = driveToState->nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void FindPuckStateTest::nextState_canReachTarget_nextStateIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	FindPuckState findPuckState(robot, field, referee, drivePuck);
	State *driveToState;
	driveToState = findPuckState.nextState();
	State *state;
	state = driveToState->nextState();

	CPPUNIT_ASSERT(state == 0);
}
