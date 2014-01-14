#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstate.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void DrivePuckToPositionStateTest::nextState_reachedTarget_nextStateIsLeavePuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	robot.setPuckCollected(true);
	DrivePuckToPositionState driveToPositionState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToPositionState.nextState();
	State *state;
	state = driveToState->nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void DrivePuckToPositionStateTest::nextState_cantReachTarget_nextStateDrivePuckToEnemyThirdState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	robot.setPuckCollected(true);
	DrivePuckToPositionState driveToPositionState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToPositionState.nextState();
	State *state;
	state = driveToState->nextState();
	DrivePuckToEnemyThirdState *stateCasted = dynamic_cast<DrivePuckToEnemyThirdState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void DrivePuckToPositionStateTest::nextState_canReachTarget_nextStateIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollected(true);
	DrivePuckToPositionState driveToPositionState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToPositionState.nextState();
	State *state;
	state = driveToState->nextState();

	CPPUNIT_ASSERT(state == 0);
	delete driveToState;
}

void DrivePuckToPositionStateTest::nextState_puckIsNotCollected_nextStateIsDriveToCollectPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	DrivePuckToPositionState driveToPositionState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = driveToPositionState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}


