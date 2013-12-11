#include "layer/strategy/fielddetectionstatemachine/turnangle.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

TurnAngle::TurnAngle(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee)
{ }

State* TurnAngle::nextState()
{
	return 0;
}

void TurnAngle::update()
{}
