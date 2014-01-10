#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void DriveToCollectPuckStateTest::nextState_numberOfKnownPucksIs0_nextStateIsFindPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, puckTargetFetcher);
	State *state;
	state = driveToCollectPuckState.nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToCollectPuckStateTest::nextState_reachedTarget_nextStateIsCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	robot.setReachedTarget(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToCollectPuckState.nextState();
	State *waitState;
	waitState = driveToState->nextState();
	waitState->update();
	waitState->update();
	waitState->update();
	waitState->update();
	waitState->update();
	State *state;
	state = waitState->nextState();
	CollectPuckState *stateCasted = dynamic_cast<CollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete waitState;
	delete driveToState;
}

void DriveToCollectPuckStateTest::nextState_canReachTarget_nextStateIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToCollectPuckState.nextState();
	State *state;
	state = driveToState->nextState();

	CPPUNIT_ASSERT(state == 0);
	delete state;
	delete driveToState;
}

void DriveToCollectPuckStateTest::nextState_cantReachTarget_nextStateIsInitialState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	robot.setCantReachedTarget(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToCollectPuckState.nextState();
	State *state;
	state = driveToState->nextState();
	InitialState *stateCasted = dynamic_cast<InitialState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void DriveToCollectPuckStateTest::nextState_cantReachTarget_nextStateIsDriveToState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	robot.setCantReachedTarget(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, puckTargetFetcher);
	State *state;
	state = driveToCollectPuckState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
