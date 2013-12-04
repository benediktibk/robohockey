#include "layer/strategy/state.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

State::State(Robot &robot, Field &field) :
    m_robot(robot),
    m_field(field)
{ }

State::~State()
{ }
