#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

CalibrationFinished::CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee) :
	State(robot, field, referee, false)
{ }

State* CalibrationFinished::nextState()
{
	return 0;
}

std::string CalibrationFinished::getName()
{
	return "CalibrationFinished";
}

void CalibrationFinished::updateInternal()
{ }
