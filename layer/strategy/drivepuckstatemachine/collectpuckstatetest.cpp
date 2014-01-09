#include "layer/strategy/drivepuckstatemachine/collectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void CollectPuckStateTest::nextState_puckCollected_nextStateIsDriveToPositionState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock drivePuck;
	robot.setPuckCollected(true);
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();
	DrivePuckToPositionState *stateCasted = dynamic_cast<DrivePuckToPositionState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::nextState_cantReachTarget_nextStatedIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock drivePuck;
	robot.setCantReachedTarget(true);
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::nextState_canReachTarget_nextStatedIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	robot.setPuckCollectable(true);
	ColorDependentPuckTargetFetcherMock drivePuck;
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	collectPuckState.update();
	state = collectPuckState.nextState();

	CPPUNIT_ASSERT(state == 0);
	delete state;
}

void CollectPuckStateTest::nextState_puckIsNotCollectable_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock drivePuck;
	CollectPuckState collectPuckState(robot, field, referee, drivePuck);
	State *state;
	state = collectPuckState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

