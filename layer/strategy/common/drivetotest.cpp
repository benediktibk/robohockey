#include "layer/strategy/common/drivetotest.h"
#include "layer/strategy/common/driveto.h"
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

void DriveToTest::nextState_didntReachedTarget_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	DriveTo driveToState(robot, field, referee, RobotPosition(), stateAfterTargetReached, stateAfterTargetUnreachable);

	driveToState.update();
	robot.setReachedTarget(false);
	robot.setStuckAtObstacle(false);

	State *state;
	state = driveToState.nextState();
	CPPUNIT_ASSERT(state == 0);
}

void DriveToTest::nextState_reachedTarget_stateAfterReachedTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	DriveTo driveToState(robot, field, referee, RobotPosition(), stateAfterTargetReached, stateAfterTargetUnreachable);

	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(false);

	State *state;
	state = driveToState.nextState();
	CPPUNIT_ASSERT(state == stateAfterTargetReached);
}

void DriveToTest::nextState_cantReachTarget_stateAfterCantReachTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	DriveTo driveToState(robot, field, referee, RobotPosition(), stateAfterTargetReached, stateAfterTargetUnreachable);

	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(false);
	robot.setCantReachedTarget(true);

	State *state;
	state = driveToState.nextState();
	CPPUNIT_ASSERT(state == stateAfterTargetUnreachable);
}

void DriveToTest::nextState_stuckAtObstacle_stateAfterCantReachTarget()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	State *stateAfterTargetReached = new StateMock(robot, field, referee);
	State *stateAfterTargetUnreachable = new StateMock(robot, field, referee);
	DriveTo driveToState(robot, field, referee, RobotPosition(), stateAfterTargetReached, stateAfterTargetUnreachable);

	driveToState.update();
	robot.setReachedTarget(true);
	robot.setStuckAtObstacle(true);

	State *state;
	state = driveToState.nextState();
	CPPUNIT_ASSERT(state == stateAfterTargetUnreachable);
}
