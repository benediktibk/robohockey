#include "layer/strategy/drivepuckstatemachine/leavepuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void LeavePuckStateTest::nextState_cantReachTarget_nextStateIsInitialState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	LeavePuckState leavePuckState(robot, field, referee, puckTargetFetcher, false);
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
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	LeavePuckState leavePuckState(robot, field, referee, puckTargetFetcher, false);
	State *state;
	state = leavePuckState.nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void LeavePuckStateTest::nextState_reachedTargetAndNumberOfKnownPucksIsNot0_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(2);
	LeavePuckState leavePuckState(robot, field, referee, puckTargetFetcher, false);

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
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	LeavePuckState leavePuckState(robot, field, referee, puckTargetFetcher, true);

	leavePuckState.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, referee.getReportedGoals());
}

void LeavePuckStateTest::update_shouldNotReportGoal_noGoalReported()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	puckTargetFetcher.setNumberOfKnownPucksNotInTarget(2);
	LeavePuckState leavePuckState(robot, field, referee, puckTargetFetcher, false);

	leavePuckState.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, referee.getReportedGoals());
}

