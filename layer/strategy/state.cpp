#include "layer/strategy/state.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

State::State(Robot &robot) :
	m_robot(robot)
{ }

State::~State()
{ }
