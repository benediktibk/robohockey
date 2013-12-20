#include "layer/strategy/drivepuckstatemachine/collectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetopositionstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/drivepuckmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void CollectPuckStateTest::nextState_puckCollected_nextStateIsDriveToPosition()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	robot.setPuckCollected(true);
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();
	DriveToPositionState *stateCasted = dynamic_cast<DriveToPositionState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void CollectPuckStateTest::nextState_cantReachTarget_nextStatedIsDriveToCollectPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	robot.setCantReachedTarget(true);
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void CollectPuckStateTest::nextState_canReachTarget_nextStatedIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DrivePuckMock *drivePuck = new DrivePuckMock();
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();

	CPPUNIT_ASSERT(state == 0);
}

