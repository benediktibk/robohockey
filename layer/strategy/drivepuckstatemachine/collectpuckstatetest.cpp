#include "layer/strategy/drivepuckstatemachine/collectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/strategy/common/colordependentpucktargetfetchermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void CollectPuckStateTest::nextState_puckCollected_nextStateIsDriveToPositionState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setPuckCollected(true);
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);
	State *state;
	state = collectPuckState.nextState();
	DrivePuckToPositionState *stateCasted = dynamic_cast<DrivePuckToPositionState*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::nextState_cantReachTarget_nextStatedIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	robot.setCantReachedTarget(true);
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);

	State *state = collectPuckState.nextState();

	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::nextState_canReachTarget_nextStatedIs0()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	robot.setPuckCollectable(true);
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);
	collectPuckState.update();

	State *state = collectPuckState.nextState();

	CPPUNIT_ASSERT(state == 0);
	delete state;
}

void CollectPuckStateTest::nextState_puckIsNotCollectable_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);
	vector<FieldObject> fieldObjects;
	fieldObjects.push_back(FieldObject(Circle(Point(1, 1), 0.1), FieldColorBlue, 1));
	field.setObjectsWithColorOrderedByDistance(fieldObjects);
	robot.setPuckCollectable(false);

	State *state = collectPuckState.nextState();

	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::nextState_puckIsCollectableButNoTargetIsLeft_nextStateIsDriveToCollectPuckState()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);
	robot.setPuckCollectable(true);
	field.setObjectsWithColorOrderedByDistance(vector<FieldObject>());

	State *state = collectPuckState.nextState();

	DriveToCollectPuckState *stateCasted = dynamic_cast<DriveToCollectPuckState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CollectPuckStateTest::update_targetLostButPuckCollectable_runThrough()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	ColorDependentPuckTargetFetcherMock puckTargetFetcher;
	CollectPuckState collectPuckState(robot, field, referee, puckTargetFetcher);
	robot.setPuckCollectable(true);
	field.setObjectsWithColorOrderedByDistance(vector<FieldObject>());

	collectPuckState.update();

	CPPUNIT_ASSERT(true);
}

