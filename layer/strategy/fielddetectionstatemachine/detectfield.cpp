#include "layer/strategy/fielddetectionstatemachine/detectfield.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DetectField::DetectField(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee)
{ }

State* DetectField::nextState()
{
	if(m_referee.detectionStart())
		return 0;
	else
		return 0;
}

void DetectField::update()
{}
