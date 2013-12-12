#include "layer/strategy/common/driveto.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "common/angle.h"
#include "common/point.h"
#include "common/robotposition.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

DriveTo::DriveTo(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee) :
	State(robot,field, referee)
{ }

State* DriveTo::nextState()
{
	return 0;
}

void DriveTo::update()
{

}
