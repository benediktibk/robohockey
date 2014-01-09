#include "layer/strategy/fielddetectionstatemachine/checkgoalcolortest.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;


void CheckGoalColorTest::nextState_successfulColorCheckNoResponse_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setTrueTeamColor(FieldColorYellow);
	referee.setTrueColorOfTeam(FieldColorUnknown);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	CalibrationFinished *stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);
}

void CheckGoalColorTest::nextState_unsuccessfulColorCheck_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setTrueTeamColor(FieldColorUnknown);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	CalibrationFinished *stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

}

void CheckGoalColorTest::nextState_successfulColorCheckGotResponse_calibrationFinished()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setTrueTeamColor(FieldColorYellow);
	referee.setTrueColorOfTeam(FieldColorUnknown);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	CalibrationFinished *stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	referee.setTrueColorOfTeam(FieldColorYellow);
	checkGoalColorState.update();

	state = checkGoalColorState.nextState();
	stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void CheckGoalColorTest::nextState_unsuccessfulChecks_guessesAfter5Tries()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setTrueTeamColor(FieldColorUnknown);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	CalibrationFinished *stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	checkGoalColorState.update();
	checkGoalColorState.update();
	checkGoalColorState.update();
	checkGoalColorState.update();

	state = checkGoalColorState.nextState();
	stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

	referee.setTrueColorOfTeam(FieldColorBlue);
	checkGoalColorState.update();

	state = checkGoalColorState.nextState();
	stateCasted = dynamic_cast<CalibrationFinished*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}



