#include "layer/strategy/fielddetectionstatemachine/detectfieldtest.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/fielddetectionstatemachine/changeposition.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"
#include "common/loggermock.h"

using namespace std;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

void DetectFieldTest::nextState_notCalibrated3Tries_turnAngle()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 0);
	field.setCalibrationReturn(false);
	detectFieldState.update();
	detectFieldState.update();
	detectFieldState.update();

	State *state = detectFieldState.nextState();

	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DetectFieldTest::nextState_notCalibrated1Try_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 0);
	field.setCalibrationReturn(false);
	detectFieldState.update();

	State *state = detectFieldState.nextState();

	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void DetectFieldTest::nextState_calibrated_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 0);
	field.setCalibrationReturnPosition(RobotPosition(Point(1,2), Angle::getEighthRotation()));
	detectFieldState.update();

	State *state = detectFieldState.nextState();

	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DetectFieldTest::nextState_calibratedOnSecondTry_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 0);
	detectFieldState.update();

	State *state = detectFieldState.nextState();

	CPPUNIT_ASSERT(state == 0);

	field.setCalibrationReturnPosition(RobotPosition(Point(1,2), Angle::getEighthRotation()));
	detectFieldState.update();
	state = detectFieldState.nextState();

	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DetectFieldTest::nextState_notCalibratedTurned7Times_turnAngle()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 7);
	detectFieldState.update();
	detectFieldState.update();
	detectFieldState.update();

	State *state = detectFieldState.nextState();
	TurnAngle *stateCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DetectFieldTest::nextState_notCalibratedTurned8Times_changePosition()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 8);
	detectFieldState.update();
	detectFieldState.update();
	detectFieldState.update();

	State *state = detectFieldState.nextState();
	ChangePosition *stateCasted = dynamic_cast<ChangePosition*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DetectFieldTest::nextState_notCalibratedTurned7Times_increasingTurnCounterCorrectly()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 7);
	detectFieldState.update();
	detectFieldState.update();
	detectFieldState.update();

	State *state = detectFieldState.nextState();
	TurnAngle *turnAngleCasted = dynamic_cast<TurnAngle*>(state);
	CPPUNIT_ASSERT(turnAngleCasted != 0);

	robot.setReachedTarget(true);
	turnAngleCasted->update();
	state = turnAngleCasted->nextState();

	DetectField *detectFieldCasted = dynamic_cast<DetectField*>(state);
	CPPUNIT_ASSERT(detectFieldCasted != 0);

	detectFieldCasted->update();
	detectFieldCasted->update();
	detectFieldCasted->update();
	state = detectFieldCasted->nextState();

	ChangePosition *changePositionCasted = dynamic_cast<ChangePosition*>(state);
	CPPUNIT_ASSERT(changePositionCasted != 0);

	delete turnAngleCasted;
	delete detectFieldCasted;
	delete changePositionCasted;
}

void DetectFieldTest::nextState_calibratedTurned8Times_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	LoggerMock logger;
	DetectField detectFieldState(robot, field, referee, logger, 8);

	field.setCalibrationReturnPosition(RobotPosition(Point(2.1,-0.9), Angle::getThreeQuarterRotation()));
	detectFieldState.update();

	State *state = detectFieldState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;

}
