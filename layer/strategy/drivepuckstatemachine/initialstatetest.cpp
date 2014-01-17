#include "layer/strategy/drivepuckstatemachine/initialstatetest.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
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

void InitialStateTest::nextState_puckCollected_nextStateIsLeavePuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollected(true);
	InitialState initialState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = initialState.nextState();
	LeavePuckState *stateCasted = dynamic_cast<LeavePuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void InitialStateTest::nextState_numberOfKnownPucksIs0_nextStateIsFindPuckTurnToState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	list<Point> targets;
	targets.push_back(Point());
	field.setTargetsForTurningToUnknownObjects(targets);
	InitialState initialState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = initialState.nextState();
	FindPuckTurnToState *stateCasted = dynamic_cast<FindPuckTurnToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void InitialStateTest::nextState_numberOfKnownPucksIs2_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	InitialState initialState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = initialState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void InitialStateTest::nextState_numberOfKnownPucksIs2AndCantReachTargetLimitIsReached_nextStateIsFindPuckTurnToPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	puckTargetFetcher.setCantReachTargetLimit(true);
	list<Point> targets;
	targets.push_back(Point());
	field.setTargetsForTurningToUnknownObjects(targets);
	InitialState initialState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = initialState.nextState();
	FindPuckTurnToState *stateCasted = dynamic_cast<FindPuckTurnToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

