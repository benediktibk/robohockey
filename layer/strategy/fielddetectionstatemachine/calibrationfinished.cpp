#include "layer/strategy/fielddetectionstatemachine/calibrationfinished.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;

CalibrationFinished::CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee) :
	State(robot, field, referee)
{

}

State* CalibrationFinished::nextState()
{
	return 0;
}

void CalibrationFinished::update()
{ }
