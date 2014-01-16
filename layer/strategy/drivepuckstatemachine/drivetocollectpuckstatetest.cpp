#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "common/loggermock.h"
#include <list>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void DriveToCollectPuckStateTest::nextState_numberOfKnownPucksIs0_nextStateIsFindPuckTurnToState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	list<Point> targets;
	targets.push_back(Point());
	field.setTargetsForTurningToUnknownObjects(targets);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = driveToCollectPuckState.nextState();
	FindPuckTurnToState *stateCasted = dynamic_cast<FindPuckTurnToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToCollectPuckStateTest::nextState_reachedTarget_nextStateIsVerifyPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	robot.setReachedTarget(true);
	field.setIsPuckcolorDetected(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = driveToCollectPuckState.nextState();
	State *waitState;
	waitState = driveToState->nextState();
	State *state;
	state = waitState->nextState();
	VerifyPuckState *stateCasted = dynamic_cast<VerifyPuckState*>(state);

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
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, logger, puckTargetFetcher);
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
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	robot.setCantReachedTarget(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, logger, puckTargetFetcher);
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
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	robot.setCantReachedTarget(true);
	DriveToCollectPuckState driveToCollectPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = driveToCollectPuckState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
