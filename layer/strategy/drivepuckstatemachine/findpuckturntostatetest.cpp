#include "layer/strategy/drivepuckstatemachine/findpuckturntostatetest.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/common/waitcyclesstate.h"
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


void FindPuckTurnToStateTest::nextState_foundPuck_nextStateIsVerifyPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	puckTargetFetcher.setNumberOfKnownPucksNotInEnemyThird(1);
	field.setIsPuckcolorDetected(true);
	list<Point> targetList;
	targetList.push_back(Point());
	FindPuckTurnToState findPuckTurnToState(robot, field, referee, logger, puckTargetFetcher, targetList);
	State *waitState;
	waitState = findPuckTurnToState.nextState();
	State *state;
	state = waitState->nextState();
	VerifyPuckState *stateCasted = dynamic_cast<VerifyPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete waitState;
}

void FindPuckTurnToStateTest::nextState_emptyTargetListAndTargetReached_nextStateIsFindPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setReachedTarget(true);
	list<Point> targetList;
	targetList.push_back(Point());
	FindPuckTurnToState findPuckTurnToState(robot, field, referee, logger, puckTargetFetcher, targetList);
	findPuckTurnToState.update();
	State *state;
	state = findPuckTurnToState.nextState();
	FindPuckState *stateCasted = dynamic_cast<FindPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void FindPuckTurnToStateTest::nextState_targetList_nextStateIsFindPuckTurnToState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	field.setIsPuckcolorDetected(true);
	robot.setReachedTarget(true);
	list<Point> targetList;
	targetList.push_back(Point());
	FindPuckTurnToState findPuckTurnToState(robot, field, referee, logger, puckTargetFetcher, targetList);
	State *waitState;
	waitState = findPuckTurnToState.nextState();
	State *state;
	state = waitState->nextState();
	FindPuckTurnToState *stateCasted = dynamic_cast<FindPuckTurnToState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
	delete waitState;
}
