#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void DrivePuckToEnemyThirdStateTest::nextState_reachedTarget_nextStateIsLeavePuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	robot.setPuckCollected(true);
	DrivePuckToEnemyThirdState driveToEnemyThirdState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToEnemyThirdState.nextState();
	State *state;
	state = driveToState->nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void DrivePuckToEnemyThirdStateTest::nextState_cantReachTarget_nextStateLeavePuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	robot.setPuckCollected(true);
	DrivePuckToEnemyThirdState driveToEnemyThirdState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToEnemyThirdState.nextState();
	State *state;
	state = driveToState->nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void DrivePuckToEnemyThirdStateTest::nextState_canReachTarget_nextStateIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollected(true);
	DrivePuckToEnemyThirdState driveToEnemyThirdState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToEnemyThirdState.nextState();
	State *state;
	state = driveToState->nextState();

	CPPUNIT_ASSERT(state == 0);
	delete driveToState;
}

void DrivePuckToEnemyThirdStateTest::nextState_puckIsNotCollected_nextStateIsDriveToCollectPuck()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	DrivePuckToEnemyThirdState driveToEnemyThirdState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = driveToEnemyThirdState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DrivePuckToEnemyThirdStateTest::nextState_stuckAtObstacle_nextStateIsLeavePuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollected(true);
	robot.setStuckAtObstacle(true);
	DrivePuckToEnemyThirdState driveToEnemyThirdState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToEnemyThirdState.nextState();
	State *state;
	state = driveToState->nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}
