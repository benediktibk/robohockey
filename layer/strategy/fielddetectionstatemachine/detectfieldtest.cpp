#include "layer/strategy/fielddetectionstatemachine/detectfieldtest.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;


void DetectFieldTest::nextState_notCalibrated_turnAngle()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DetectField detectFieldState(robot, field, referee);

	field.setCalibrationReturn(false);

	State *state;
	state = detectFieldState.nextState();
	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);

}



