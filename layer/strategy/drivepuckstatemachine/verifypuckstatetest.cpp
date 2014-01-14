#include "layer/strategy/drivepuckstatemachine/verifypuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
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


void VerifyPuckStateTest::nextState_correctPuckIsCollectable_nextStateIsCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollectable(true);
	field.setIsPuckOfColorInFront(true);
	VerifyPuckState verifyPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = verifyPuckState.nextState();
	CollectPuckState *stateCasted = dynamic_cast<CollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void VerifyPuckStateTest::nextState_wrongPuckIsCollectable_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollectable(true);
	VerifyPuckState verifyPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = verifyPuckState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void VerifyPuckStateTest::nextState_correctPuckIsNotCollectable_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	field.setIsPuckOfColorInFront(true);
	VerifyPuckState verifyPuckState(robot, field, referee, logger, puckTargetFetcher);
	State *state;
	state = verifyPuckState.nextState();
	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}


