#include "layer/strategy/drivepuckstatemachine/leavepuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
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

void LeavePuckStateTest::nextState_cantReachTarget_nextStateIsInitialState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	LeavePuckState leavePuckState(robot, field, referee, logger, puckTargetFetcher, false);
	State *state;
	state = leavePuckState.nextState();
	InitialState *stateCasted = dynamic_cast<InitialState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void LeavePuckStateTest::nextState_reachedTargetAndNumberOfKnownPucksIs0_nextStateIsFindPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	list<Point> targets;
	targets.push_back(Point());
	field.setTargetsForTurningToUnknownObjects(targets);
	LeavePuckState leavePuckState(robot, field, referee, logger, puckTargetFetcher, false);
	State *state;
	state = leavePuckState.nextState();
	FindPuckTurnToState *stateCasted = dynamic_cast<FindPuckTurnToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void LeavePuckStateTest::nextState_reachedTargetAndNumberOfKnownPucksIsNot0_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	LeavePuckState leavePuckState(robot, field, referee, logger, puckTargetFetcher, false);

	State *state = leavePuckState.nextState();

	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void LeavePuckStateTest::update_shouldReportGoal_oneGoalReported()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	LeavePuckState leavePuckState(robot, field, referee, logger, puckTargetFetcher, true);

	leavePuckState.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, referee.getReportedGoals());
}

void LeavePuckStateTest::update_shouldNotReportGoal_noGoalReported()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	LeavePuckState leavePuckState(robot, field, referee, logger, puckTargetFetcher, false);

	leavePuckState.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, referee.getReportedGoals());
}

