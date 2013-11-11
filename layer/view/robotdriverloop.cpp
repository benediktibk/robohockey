#include "layer/view/robotdriverloop.h"
#include "layer/view/robotdriver.h"

using namespace RoboHockey::Layer::View;

RobotDriverLoop::RobotDriverLoop(RobotDriver &driver) :
	m_intervalInMilliSeconds(100),
	m_driver(driver)
{
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(callUpdateAndRestart()));
	m_timer.start(m_intervalInMilliSeconds);
}

void RobotDriverLoop::callUpdateAndRestart()
{
	m_driver.update();
	m_timer.start(m_intervalInMilliSeconds);
}
