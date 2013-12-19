#include "layer/strategy/fielddetectionstatemachine/detectfieldtest.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/driveto.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;


void DetectFieldTest::nextState_notCalibrated3Tries_turnAngle()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DetectField detectFieldState(robot, field, referee);

	field.setCalibrationReturn(false);
	detectFieldState.update();
	detectFieldState.update();
	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void DetectFieldTest::nextState_notCalibrated1Try_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DetectField detectFieldState(robot, field, referee);

	field.setCalibrationReturn(false);
	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void DetectFieldTest::nextState_calibrated_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DetectField detectFieldState(robot, field, referee);

	field.setCalibrationReturn(true);
	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	DriveTo *stateCasted = dynamic_cast<DriveTo*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void DetectFieldTest::nextState_calibratedOnSecondTry_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	DetectField detectFieldState(robot, field, referee);

	field.setCalibrationReturn(false);
	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	DriveTo *stateCasted = dynamic_cast<DriveTo*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	field.setCalibrationReturn(true);
	detectFieldState.update();

	state = detectFieldState.nextState();
	stateCasted = dynamic_cast<DriveTo*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);

}
