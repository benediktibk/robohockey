#include "layer/strategy/common/state.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

State::State(Robot &robot, Field &field, Referee &referee) :
    m_robot(robot),
    m_field(field),
    m_referee(referee)
{ }

State::~State()
{ }
