#include "layer/strategy/fielddetectionstatemachine/checkgoalcolortest.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/statemachine.h"
#include "layer/strategy/common/statemock.h"
#include "layer/strategy/common/refereemock.h"
#include "layer/strategy/common/driveto.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;


void CheckGoalColorTest::nextState_successfulColorCheck_driveToWaitingPosition()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setOwnTeamColor(FieldObjectColorYellow);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	DriveTo *stateCasted = dynamic_cast<DriveTo*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void CheckGoalColorTest::nextState_unsuccessfulColorCheck_NULL()
{
	RobotMock robot;
	FieldMock field;
	RefereeMock referee;
	CheckGoalColor checkGoalColorState(robot, field, referee);

	field.setOwnTeamColor(FieldObjectColorUnknown);
	checkGoalColorState.update();

	State *state;
	state = checkGoalColorState.nextState();
	DriveTo *stateCasted = dynamic_cast<DriveTo*>(state);
	CPPUNIT_ASSERT(stateCasted == 0);

}



