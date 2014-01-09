#include "layer/strategy/common/drivetostatetest.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/point.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void DriveToStateTest::nextState_didntReachedTarget_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition());
	DriveToState driveToState(robot, field, referee, targetList, stateAfterTargetReached, stateAfterTargetUnreachable);
	driveToState.update();
	robot.setReachedTarget(false);
	robot.setStuckAtObstacle(false);

	State *state = driveToState.nextState();

	CPPUNIT_ASSERT(state == 0);
}

void DriveToStateTest::nextState_reachedTarget_stateAfterReachedTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition());
	DriveToState driveToState(robot, field, referee, targetList, stateAfterTargetReached, stateAfterTargetUnreachable);
	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(false);

	State *state = driveToState.nextState();

	CPPUNIT_ASSERT(state == stateAfterTargetReached);
	delete state;
}

void DriveToStateTest::nextState_cantReachTarget_stateAfterCantReachTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition());
	DriveToState driveToState(robot, field, referee, targetList, stateAfterTargetReached, stateAfterTargetUnreachable);
	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(false);
	robot.setCantReachedTarget(true);

	State *state = driveToState.nextState();

	CPPUNIT_ASSERT(state == stateAfterTargetUnreachable);
	delete state;
}

void DriveToStateTest::nextState_stuckAtObstacle_stateAfterCantReachTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	list<RobotPosition> targetList;
	targetList.push_back(RobotPosition());
	DriveToState driveToState(robot, field, referee, targetList, stateAfterTargetReached, stateAfterTargetUnreachable);
	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(true);

	State *state = driveToState.nextState();

	CPPUNIT_ASSERT(state == stateAfterTargetUnreachable);
	delete state;
}
