#include "layer/strategy/fielddetectionstatemachine/detectfieldtest.h"
#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

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
	DetectField detectFieldState(robot, field, referee, list<pair<unsigned int, RobotPosition> >());

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
	DetectField detectFieldState(robot, field, referee, list<pair<unsigned int, RobotPosition> >());

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
	list<pair<unsigned int, RobotPosition> > calibratedData;
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));

	DetectField detectFieldState(robot, field, referee, calibratedData);

	field.setCalibrationReturnPosition(RobotPosition(Point(1,2), Angle::getEighthRotation()));
	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void DetectFieldTest::nextState_calibratedOnSecondTry_driveTo()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	list<pair<unsigned int, RobotPosition> > calibratedData;
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));

	DetectField detectFieldState(robot, field, referee, calibratedData);

	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	field.setCalibrationReturnPosition(RobotPosition(Point(1,2), Angle::getEighthRotation()));
	detectFieldState.update();

	state = detectFieldState.nextState();
	stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);

}

void DetectFieldTest::nextState_calibrationSuccessfulButTooFewCalibrationResults_turnAngle()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	list<pair<unsigned int, RobotPosition> > calibratedData;
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));
	calibratedData.push_back(pair<unsigned int, RobotPosition>(3, RobotPosition(Point(), Angle())));

	DetectField detectFieldState(robot, field, referee, calibratedData);

	detectFieldState.update();

	State *state;
	state = detectFieldState.nextState();
	DriveToState *stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	field.setCalibrationReturnPosition(RobotPosition(Point(1,2), Angle::getEighthRotation()));
	detectFieldState.update();

	state = detectFieldState.nextState();
	stateCasted = dynamic_cast<DriveToState*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}
