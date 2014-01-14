#include "layer/strategy/drivepuckstatemachine/findpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

void FindPuckStateTest::nextState_targetReached_nextStateIsVerifyPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	field.setIsPuckcolorDetected(true);
	FindPuckState findPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState = findPuckState.nextState();
	State *waitState;
	waitState = driveToState->nextState();
	State *state;
	state = waitState->nextState();
	VerifyPuckState *stateCasted = dynamic_cast<VerifyPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
	delete waitState;
}

void FindPuckStateTest::nextState_cantReachTarget_nextStateIsFindPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	FindPuckState findPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = findPuckState.nextState();
	State *state;
	state = driveToState->nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete driveToState;
}

void FindPuckStateTest::nextState_canReachTarget_nextStateIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	FindPuckState findPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *driveToState;
	driveToState = findPuckState.nextState();
	State *state;
	state = driveToState->nextState();

	CPPUNIT_ASSERT(state == 0);
	delete driveToState;
}
