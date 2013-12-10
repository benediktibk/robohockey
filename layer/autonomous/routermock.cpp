#include "layer/autonomous/routermock.h"
#include "layer/autonomous/route.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

RouterMock::RouterMock() :
	m_chessMode(false)
{ }

Route RouterMock::calculateRoute(const RobotPosition &start, const RobotPosition &end, const Field &) const
{
	Route route(0.38);
	route.addPoint(start.getPosition());
	if (m_chessMode)
		route.addPoint(Point(start.getPosition().getX(), end.getPosition().getY()));
	route.addPoint(end.getPosition());
	return route;
}

void RouterMock::setChessMode(bool value)
{
	m_chessMode = value;
}
