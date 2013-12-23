#include "layer/strategy/fielddetectionstatemachine/turnangletest.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/angle.h"
#include "common/compare.h"
#include <vector>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;


void TurnAngleTest::nextState_targetReached_detectField()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	TurnAngle turnAngleState(robot, field, referee, Angle::getThreeQuarterRotation(), vector<RobotPosition>());

	turnAngleState.update();
	robot.setReachedTarget(true);

	State *state;
	state = turnAngleState.nextState();
	DetectField *stateCasted = dynamic_cast<DetectField*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void TurnAngleTest::nextState_targetNotReached_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	TurnAngle turnAngleState(robot, field, referee, Angle::getThreeQuarterRotation(), vector<RobotPosition>());

	turnAngleState.update();
	robot.setReachedTarget(false);

	State *state;
	state = turnAngleState.nextState();
	DetectField *stateCasted = dynamic_cast<DetectField*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void TurnAngleTest::update_quarterRotation_robotGetsCorrectTarget()
{
	Compare compare(0.01);

	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	TurnAngle turnAngleState(robot, field, referee, Angle::getQuarterRotation(), vector<RobotPosition>());

	turnAngleState.update();

	Point resultPoint(robot.getLastTurnToTarget());
	Angle resultAngle(robot.getCurrentPosition().getPosition(), resultPoint);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), resultAngle));
}



