#include "layer/strategy/fielddetectionstatemachine/changepositiontest.h"
#include "layer/strategy/fielddetectionstatemachine/changeposition.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;


void ChangePositionTest::nextState_didntReachedTarget_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ChangePosition changePositionState (robot, field, referee, logger);

	changePositionState.update();
	State *state = changePositionState.nextState();

	CPPUNIT_ASSERT(state == 0);
}

void ChangePositionTest::nextState_cantReachTarget_detectField()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ChangePosition changePositionState (robot, field, referee, logger);

	robot.setCantReachedTarget(true);
	changePositionState.update();
	State *state = changePositionState.nextState();
	State *stateCasted = dynamic_cast<DetectField*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}

void ChangePositionTest::nextState_reachedTarget_detectField()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	ChangePosition changePositionState (robot, field, referee, logger);

	robot.setReachedTarget(true);
	changePositionState.update();
	State *state = changePositionState.nextState();
	State *stateCasted = dynamic_cast<DetectField*>(state);

	CPPUNIT_ASSERT(stateCasted != 0);
}
